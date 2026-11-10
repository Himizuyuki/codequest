# Messenger Pigeons (fork, pipe, exec)

Threads share one memory. **Processes** share nothing: each has its own copy of everything, and they talk
through the kernel - exit codes, signals, pipes. Time to breed some child processes and send pigeons
between them. (POSIX only: Linux, macOS, WSL.)

```cpp
int run_child(const std::function<int()>& child_main);

std::string capture(const std::function<void()>& child_main);

struct Result {
    int status;
    std::string out;
};
Result run_program(const std::vector<std::string>& argv);
```

- **`run_child`** forks. The **child** process calls `child_main()` and exits with its return value as exit
  code. The **parent** waits for the child and returns how it ended: the exit code if it exited normally, or
  `128 + signal number` if a signal killed it (the convention shells use).
- **`capture`** forks a child whose **standard output goes into a pipe**, runs `child_main()` in it, and
  returns everything the child wrote to stdout, as a string. It works whether the child writes with
  `write(1, ...)`, `printf` or `std::cout`, and for outputs of any size.
- **`run_program`** runs an external program: `argv[0]` is looked up in `PATH`, the rest are its arguments
  (no shell involved, so spaces in an argument stay in that argument). It returns the program's stdout and
  its status, computed as in `run_child`. If the program cannot be started, the status is `127`.

Rules for all three:

- The child process must **never return** into the caller: it ends inside your function, with `_exit`.
- No **zombies**: every child is waited for before the function returns.
- No **leaked file descriptors**: every pipe end is closed. The tests call `capture` thousands of times.

## Examples

```cpp
run_child([] { return 7; });                          // 7
run_child([] { raise(SIGKILL); return 0; });          // 137  (128 + 9)

capture([] { std::printf("coo\n"); });                // "coo\n"

run_program({"echo", "hello", "world"});              // {0, "hello world\n"}
run_program({"sh", "-c", "exit 3"});                  // {3, ""}
run_program({"no-such-program-anywhere"});            // {127, ""}
```

## Notes

- A `timeout` result usually means the parent is waiting for an end-of-file that never comes (a write end of
  the pipe is still open somewhere) or is in `waitpid` while the child is blocked writing to a full pipe.
- You may assume `fork` and `pipe` succeed; in real code, check every return value.
