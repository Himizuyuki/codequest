# Lesson: processes, fork, pipes and exec

## Thread or process?
| | Threads | Processes |
|---|---|---|
| Memory | shared | separate (copied lazily: copy-on-write) |
| Talking to each other | just read the variable (and lock it) | pipes, sockets, files, shared memory, signals |
| A crash | kills the whole program | kills one process; the others survive |
| Cost to create | ~10 microseconds | ~100+ microseconds |
| Typical bug | data race, deadlock | zombie, leaked descriptor, pipe deadlock |

Browsers, databases like PostgreSQL and every shell use processes for isolation.

## fork: one call, two returns
```cpp
pid_t pid = fork();
if (pid == 0) {
    // child: a copy of the parent at this instant. Its changes are invisible to the parent.
    _exit(do_work());
}
// parent: pid is the child's process id
int status;
waitpid(pid, &status, 0);
if (WIFEXITED(status))   code = WEXITSTATUS(status);   // exited: 0..255
if (WIFSIGNALED(status)) sig  = WTERMSIG(status);      // killed by a signal
```

## Pipes
`pipe(fd)` gives two file descriptors: bytes written to `fd[1]` come out of `fd[0]`. After `fork` both
processes hold both ends; each closes the end it does not use.

```cpp
int fd[2];
pipe(fd);
if (fork() == 0) {
    dup2(fd[1], STDOUT_FILENO);    // "stdout now means the pipe"
    close(fd[0]); close(fd[1]);    // the originals are no longer needed
    ...
    _exit(0);
}
close(fd[1]);                      // parent: MUST close its write end
while ((n = read(fd[0], buf, sizeof buf)) > 0) out.append(buf, n);
close(fd[0]);
waitpid(pid, &status, 0);
```

## exec: become another program
`execvp(file, argv)` replaces the current process image with a new program. On success it **never returns**;
the line after it runs only on failure. `fork` + `exec` + `wait` is how every shell runs a command.

```cpp
std::vector<char*> args;                                   // argv must be a null-terminated char* array
for (const auto& s : argv) args.push_back(const_cast<char*>(s.c_str()));
args.push_back(nullptr);
execvp(args[0], args.data());
_exit(127);                                                // only reached if exec failed
```

## Quirks (the interview questions)
1. **`_exit`, not `exit` or `return`, in a forked child.** `exit` runs `atexit` handlers and flushes stdio
   buffers that were *copied* from the parent - output appears twice. `return` is worse: the child keeps
   running the parent's program.
2. **The double-print bug.** `printf("hi"); fork();` prints "hi" twice when stdout is a file or pipe: the
   unflushed buffer was duplicated. `fflush(stdout)` (or `std::cout.flush()`) before `fork`.
3. **EOF needs every write end closed.** `read` returns 0 only when *no* process has the write end open -
   including the reader itself. Forgetting `close(fd[1])` in the parent hangs forever.
4. **Pipes are small** (64 KiB on Linux). Writer blocks when full, reader blocks when empty. `waitpid` before
   reading deadlocks on big outputs: drain first, then wait.
5. **Zombies and orphans.** A finished child stays in the process table as a zombie until its parent calls
   `wait`. If the parent dies first, the child is an orphan and is adopted by `init`.
6. **The exit code is 8 bits.** `exit(300)` is seen as `44`; `exit(-1)` as `255`.
7. **File descriptors are inherited** across `fork` *and* `exec`. Leaking them into children is a bug and a
   security hole: open with `O_CLOEXEC` / use `pipe2(fd, O_CLOEXEC)`.
8. **`fork` in a multithreaded program** copies only the calling thread. Mutexes held by other threads stay
   locked forever in the child - so between `fork` and `exec` call only async-signal-safe functions
   (`malloc` and `printf` are not). `posix_spawn` avoids the issue.
9. **Writing to a pipe nobody reads** raises `SIGPIPE`, which kills the writer by default. That is how
   `yes | head -1` terminates.
10. **`read` and `write` can be partial or interrupted** (`EINTR`): always loop.
11. **Race conditions exist between processes too**: two processes appending to one file, check-then-create
    of a lock file (`O_CREAT | O_EXCL` makes it atomic), signals arriving at any instruction.

## Standard C++?
There is no process API in the C++ standard library (C++26 still has none; `std::system` only runs a shell
command). Real code uses POSIX as above, `posix_spawn`, or a library such as Boost.Process.
