# Concurrency: threads, processes and race conditions

The vocabulary and the traps, with the problem that practises each. Lessons 5.3 to 5.8 have the details.

## Threads vs processes
| | Threads | Processes |
|---|---|---|
| Memory | shared | separate (copy-on-write after `fork`) |
| Communication | shared variables + synchronisation | pipes, sockets, files, shared memory, signals |
| A crash | takes down the whole program | isolated |
| Creation | cheap (`std::jthread`) | dearer (`fork`, `posix_spawn`) |
| Typical bugs | data race, deadlock | zombie, leaked descriptor, pipe deadlock |

Concurrency = dealing with several things at once (structure). Parallelism = doing several things at once
(needs several cores).

## The four bugs
| Bug | What it is | Fix | Practise |
|---|---|---|---|
| **Data race** | two threads touch one variable, one writes, no synchronisation: undefined behavior | mutex, atomic, or do not share | 5.3 |
| **Race condition** | result depends on timing even though each access is safe (check-then-act) | one critical section, or compare-exchange | 5.4, 5.7 |
| **Deadlock** | a cycle of threads each holding what the next one wants | lock ordering, `std::scoped_lock`, fewer locks | 5.4 |
| **Lost wakeup** | a thread sleeps on a condition nobody will signal again | predicate waits, `notify_all`, wake on shutdown | 5.5, 5.6 |

Also: **starvation** (a thread never gets its turn), **livelock** (threads keep reacting to each other and
make no progress), **priority inversion**, **false sharing** (performance only).

## Toolbox
| Tool | For |
|---|---|
| `std::jthread` (C++20) | a thread that joins itself; `std::stop_token` to ask it to stop |
| `std::mutex` + `std::lock_guard` | one critical section |
| `std::scoped_lock(a, b)` | several mutexes, deadlock-free |
| `std::unique_lock` | when you must unlock early or wait on a condition variable |
| `std::shared_mutex` + `std::shared_lock` | many readers, rare writers |
| `std::condition_variable` | sleep until a predicate on shared state becomes true |
| `std::atomic<T>` | one counter/flag/pointer; `compare_exchange` for check-and-update |
| `std::call_once`, function-local `static` | run-once initialisation |
| `std::counting_semaphore`, `std::latch`, `std::barrier` (C++20) | permits, start gun, meeting point |
| `std::async` / `std::future` / `std::promise` | get one result back from another thread |
| `thread_local` | one copy of a variable per thread |

## Rules that keep you out of trouble
1. Share as little as possible. Immutable or thread-private data needs no lock.
2. Every shared variable has exactly one mutex guarding it; say which one in a comment.
3. Lock with RAII guards only. Keep critical sections short; never call unknown code while holding a lock.
4. Always wait with a predicate: `cv.wait(lock, [&] { return ready; });`
5. Take multiple locks in one fixed order, or with `std::scoped_lock`.
6. Every blocking operation needs a way to be cancelled (a `closed` flag, a `stop_token`).
7. `sleep_for` is never a synchronisation tool.
8. A test passing proves nothing about races. Use `-fsanitize=thread`, and reason.

## Processes cheat sheet (POSIX)
```cpp
pid_t pid = fork();                 // 0 in the child, the child's pid in the parent
if (pid == 0) { execvp(argv[0], argv); _exit(127); }
int status; waitpid(pid, &status, 0);
WIFEXITED(status) ? WEXITSTATUS(status) : 128 + WTERMSIG(status);

int fd[2]; pipe(fd);                // fd[0] read end, fd[1] write end
dup2(fd[1], STDOUT_FILENO);         // redirect stdout into the pipe
```
Flush before `fork`; `_exit` in the child; close the unused pipe ends (EOF arrives only when *all* write ends
are closed); read before you wait; wait for every child. Practise: 5.8.

## Questions interviewers actually ask
- Difference between a process and a thread? Between a mutex and a semaphore? Between a data race and a race
  condition?
- What are the conditions for deadlock, and how do you prevent it?
- What is a spurious wakeup? Why `while` and not `if` around `wait`?
- Implement a thread-safe queue / bounded buffer / thread pool. (5.5)
- Print numbers in order from N threads. (5.6)
- Make this singleton thread-safe. What is wrong with double-checked locking? (5.7)
- What does `volatile` do? (Nothing for threads in C++.) What is `std::atomic`? What is the ABA problem?
- What happens to a child process when the parent exits? What is a zombie? (5.8)
- How would you find a data race or a deadlock in production? (ThreadSanitizer; `gdb`, `thread apply all bt`.)
