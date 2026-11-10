# Lesson: mutexes, race conditions and deadlock

## Data race vs race condition
They are different bugs:

- **Data race**: two threads access the same memory, at least one writes, no synchronisation. Undefined behavior.
- **Race condition**: the result depends on timing, even if every single access is protected.

```cpp
if (balance(from) >= amount) {      // locked inside balance()... and unlocked again
    withdraw(from, amount);         // another thread emptied the account in between
}
```
No data race, still wrong: this is **check-then-act** (also called TOCTOU, time of check to time of use). The
check and the action must sit inside *one* critical section.

## The mutex toolbox
```cpp
std::mutex m;
{ std::lock_guard lock(m);  /* critical section */ }   // unlocks at the brace, even if an exception flies
std::unique_lock lock(m);            // movable, can unlock()/lock() again; needed for condition variables
std::scoped_lock lock(a, b);         // several mutexes at once, deadlock-free
std::shared_mutex rw;                // many readers (std::shared_lock) or one writer (std::unique_lock)
```
Never call `m.lock()` / `m.unlock()` by hand: an early `return` or exception leaves it locked forever.

A `const` method that locks needs `mutable std::mutex m;`.

## Deadlock
Four conditions must all hold (Coffman): mutual exclusion, hold-and-wait, no pre-emption, and a **cycle** of
threads each waiting for the next. Break any one. In practice you break the cycle:

1. **Lock ordering**: everyone takes locks in the same global order (lowest account index first).
2. **`std::scoped_lock(a, b)`** (or `std::lock(a, b)`): takes all or none, backing off and retrying.
3. **Hold one lock at a time**, or just use one coarser lock.

## Quirks
1. **`std::scoped_lock lock;`** with no arguments compiles and locks nothing. So does
   `std::lock_guard<std::mutex>(m);` - that declares a temporary (or even a variable named `m`!) that dies
   at the semicolon. Always name the guard.
2. **Locking the same `std::mutex` twice from one thread is undefined behavior** (usually a hang).
   `scoped_lock(m[i], m[i])` does exactly that. `std::recursive_mutex` exists, but needing it usually means the
   design is tangled.
3. **A mutex cannot be copied or moved**, so a class holding one loses its default copy/move, and
   `std::vector<std::mutex>` can only be sized at construction (`std::vector<std::mutex> m(n);`).
4. **A consistent read needs the lock too.** Summing balances without holding every lock can see a transfer
   half done.
5. **Keep critical sections short** and never call unknown code (callbacks, virtual functions, I/O) while
   holding a lock - that is how surprise deadlocks happen.
6. **Coarse vs fine locking**: one big lock is simple and often fast enough. Per-object locks scale but multiply
   the ways to deadlock. Say this trade-off out loud in an interview.

## Tools
Compile with `-fsanitize=thread` to catch data races and lock-order inversions at run time. When a program
hangs, `gdb -p <pid>` then `thread apply all bt` shows every thread parked in `__lll_lock_wait`.
