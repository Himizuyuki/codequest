# Lesson: condition variables and producer/consumer

A mutex answers "who may touch this now?". A **condition variable** answers "wake me when something changed".

## The one pattern to memorise
```cpp
std::mutex m;
std::condition_variable cv;
std::deque<int> items;

// waiting side
std::unique_lock lock(m);                         // unique_lock, not lock_guard: wait() must unlock it
cv.wait(lock, [&] { return !items.empty(); });    // sleeps; re-checks the condition every time it wakes
int x = items.front(); items.pop_front();         // here the lock is held AND the condition is true

// notifying side
{ std::lock_guard lock(m); items.push_back(42); } // change the state under the same mutex
cv.notify_one();
```
`wait(lock, pred)` is exactly `while (!pred()) wait(lock);`. While asleep the mutex is released; on waking it
is re-acquired before `pred` runs.

## Quirks (each one is an interview question)
1. **Spurious wakeups.** `wait` may return although nobody notified. With `if (empty) cv.wait(lock);` you then
   pop from an empty queue. Always wait in a loop, or pass the predicate.
2. **Lost wakeups.** A notification is not remembered: if nobody is waiting, it evaporates. That is harmless
   only when the waiter checks the condition under the mutex *before* sleeping, and the notifier changes the
   condition under the same mutex. Change state without the lock and a waiter can check, get pre-empted,
   miss the notify, then sleep forever.
3. **`notify_one` vs `notify_all`.** `notify_one` wakes a single, arbitrary waiter. If waiters wait for
   *different* conditions on the same condition variable (producers and consumers sharing one), the wrong
   one may wake, see nothing to do, and go back to sleep: everybody hangs. Either use one condition variable
   per condition (`not_full`, `not_empty`) or `notify_all`.
4. **Shutdown.** Blocked threads need a way out. A `closed` flag has to be part of *every* predicate, and
   `close()` must `notify_all` - otherwise `jthread` destructors join forever.
5. **`std::condition_variable` only works with `std::unique_lock<std::mutex>`.** `condition_variable_any`
   accepts other locks and, in C++20, a `std::stop_token` so that `request_stop()` wakes the waiter.
6. **Notify inside or outside the lock?** Both are correct. Outside avoids waking a thread that immediately
   blocks on the mutex; inside is easier to reason about.

## Why bounded?
An unbounded queue hides overload: if producers are faster than consumers, memory grows until the process
dies. A bound gives **back-pressure** - fast producers are slowed to the consumers' pace.

## C++20 alternatives
`std::counting_semaphore` (two semaphores, "free slots" and "filled slots", plus a mutex give the same queue),
`std::latch`, `std::barrier`, and `std::atomic<T>::wait()` / `notify_one()` for single values.

## Follow-ups to expect
- Make it a template; move values in (`push(T&&)`) and out.
- `try_push` / `try_pop` and versions with a timeout (`wait_for`).
- A thread pool = this queue holding `std::function<void()>` + N worker threads popping in a loop.
- "Lock-free" single-producer/single-consumer ring buffer with two atomics.
