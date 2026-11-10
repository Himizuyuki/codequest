# Lesson: threads, data races and atomics

## Starting threads
```cpp
#include <thread>
{
    std::jthread worker([&] { do_work(); });   // starts running immediately
}                                              // jthread joins here, automatically
```
**C++20 quirk:** a `std::thread` that is still joinable when destroyed calls `std::terminate()` - forget one
`join()` (or throw an exception before it) and the program dies. `std::jthread` joins in its destructor and
also supports cooperative cancellation (`std::stop_token`). Prefer it.

## Data race = undefined behavior
Two threads touching the same variable, at least one writing, without synchronisation, is a **data race**. It is
not "a slightly wrong result": it is undefined behavior. `counter++` is really *load, add, store*; two threads
interleave and one increment disappears.

Three ways out:

| Tool | Use when |
|---|---|
| **No sharing** | best: each thread writes only its own data (its own slot of a vector), results combined after joining |
| `std::atomic<T>` | a single counter/flag: `fetch_add`, `load`, `store`, `compare_exchange_*` |
| `std::mutex` + `std::lock_guard` / `std::scoped_lock` | several variables that must change together |

```cpp
std::atomic<long long> n{0};
n.fetch_add(1);            // or ++n : one indivisible step

std::mutex m;
{ std::lock_guard lock(m); /* touch shared state */ }      // unlocks at the brace, even on exceptions
```

## Splitting work
Give thread `t` the half-open slice `[begin, end)` and a private accumulator; write the result to `partial[t]`
once at the end. Reading the shared `const` input from many threads is fine - only writes race.

## Quirks
1. **Captures and lifetime.** A thread's lambda capturing locals by reference is only safe if the thread is joined
   before those locals die. With `jthread` objects in a vector declared *after* the data, destruction order
   (reverse of declaration) does the right thing. Loop variables must be captured **by value**.
2. **`vector<bool>` is not thread-safe per element** (bits share bytes). `vector<char>` is.
3. **False sharing.** Threads writing to *neighbouring* elements fight over the same cache line; correctness is
   fine but speed collapses. Accumulate in a local variable and store once.
4. **Atomics are not magic.** `if (n == 0) n = 1;` on an atomic is two operations - still a race in logic. Use
   `compare_exchange`.
5. **More threads is not always faster.** Thread start-up costs tens of microseconds; for small inputs the
   single-threaded loop wins. `std::thread::hardware_concurrency()` tells you how many cores exist.
6. **Deadlock:** two threads locking two mutexes in opposite order. `std::scoped_lock(a, b)` locks both safely.

## Also in C++20
`std::atomic<T>::wait`/`notify_one`, `std::atomic<std::shared_ptr<T>>`, `std::counting_semaphore`, `std::latch`,
`std::barrier`, and `std::stop_token`. The compiler flag `-fsanitize=thread` finds data races at run time.
