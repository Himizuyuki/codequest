# Lesson: making threads take turns

Threads give you no ordering at all: `std::jthread a(f), b(g);` may run `g` first, interleave them, or run them
truly in parallel. Any order you need, you must build from shared state plus waiting.

## The recipe
1. Put the *whole* protocol state in plain variables: here just `int turn`.
2. Protect it with one mutex.
3. Each thread waits for *its* condition on that state: `cv.wait(lock, [&] { return turn == id; });`
4. After acting, update the state and wake the others.

```cpp
void run(int id, const std::function<void()>& leg) {
    std::unique_lock lock(m);
    cv.wait(lock, [&] { return turn == id; });
    leg();
    turn = (turn + 1) % runners;
    lock.unlock();
    cv.notify_all();
}
```

## Why `notify_all` here
All runners wait on the same condition variable, each for a different condition. `notify_one` wakes one waiter
chosen by the system. If it picks runner 2 when the turn is 1, runner 2 checks, sleeps again - and the
notification is used up. Runner 1 never wakes: **deadlock by lost wakeup**. It may work a thousand times on
your machine first.

Rule: `notify_one` only when *any* waiter can make progress (identical workers taking jobs from a queue).
Otherwise `notify_all`, or one condition variable per runner.

`notify_all` causes a "thundering herd" (everyone wakes, all but one sleep again). For a handful of threads that
is fine; for hundreds, give each waiter its own condition variable or semaphore.

## Quirks
1. **Sleeping is not synchronisation.** `sleep_for(10ms)` "so the other thread goes first" works until the
   machine is busy. Interviewers treat it as a wrong answer.
2. **Holding the lock while running `leg()`** is the simple way to guarantee legs never overlap. The cost: if
   `leg` is slow, or calls back into `run`, everything stalls (or self-deadlocks). The alternative is to
   release the lock during `leg()` - correct here too, because nobody else's `turn == id` can be true meanwhile.
3. **Exceptions.** If `leg()` throws, the baton must still move on, or every other runner hangs. A small RAII
   guard does it.
4. **Fairness is not guaranteed** by mutexes or condition variables. If you need a strict order, encode the
   order in the state, as here.

## The C++20 way: waiting on an atomic
```cpp
std::atomic<int> turn{0};

for (int t = turn.load(); t != id; t = turn.load()) turn.wait(t);   // sleeps while turn == t
leg();
turn.store((id + 1) % runners);
turn.notify_all();
```
`wait(old)` blocks only while the value still equals `old`, so a change between your `load` and your `wait` is
not missed. No mutex needed for a single value. Other C++20 tools: `std::binary_semaphore` (one per runner:
release the next runner's semaphore), `std::latch` (start gun), `std::barrier` (everyone meets each lap).
