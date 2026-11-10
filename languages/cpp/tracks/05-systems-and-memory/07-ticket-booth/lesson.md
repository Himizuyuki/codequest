# Lesson: atomics, compare-exchange and doing things once

## Each operation is atomic; a sequence is not
```cpp
std::atomic<int> left{1};
if (left > 0)      // thread A reads 1          thread B reads 1
    --left;        // A writes 0                B writes -1   -> two tickets sold, one existed
```
No data race (every access is atomic), yet the logic races: **check-then-act**. The check and the write
must be one indivisible step.

## Compare-and-swap (CAS)
```cpp
bool ok = a.compare_exchange_strong(expected, desired);
```
Atomically: *if `a == expected`, set `a = desired` and return true; otherwise copy `a`'s current value into
`expected` and return false.* The standard loop:

```cpp
int seen = left.load();
while (seen > 0) {
    if (left.compare_exchange_weak(seen, seen - 1)) return true;   // nobody interfered: sold
    // somebody changed it; `seen` now holds the fresh value, and the loop condition re-checks it
}
return false;
```
- `_weak` may fail spuriously (even when the value matched) - fine inside a loop, and cheaper on some CPUs.
  `_strong` only fails when the value really differs: use it when there is no loop.
- Forgetting that `expected` is **overwritten on failure** is the classic CAS bug.
- **ABA problem**: the value went A -> B -> A and your CAS succeeds although the world changed. Harmless for a
  counter; deadly for lock-free linked lists (the node at that address may be a different node now).

## Doing something exactly once
Double-checked locking written by hand is famously easy to get wrong:
```cpp
if (!ready) { std::lock_guard l(m); if (!ready) { value = make(); ready = true; } }   // `ready` must be atomic!
```
Use the library:
```cpp
std::once_flag once;
std::call_once(once, [&] { value = make(); });   // late callers wait for the first one to finish
```
and for a global/singleton, a function-local static - its initialisation is thread-safe since C++11
("magic statics"):
```cpp
Config& config() { static Config c = load(); return c; }
```

## A spinlock
```cpp
std::atomic_flag busy;                                    // C++20: default-constructed means clear
void lock()   { while (busy.test_and_set(std::memory_order_acquire)) { /* spin */ } }
void unlock() { busy.clear(std::memory_order_release); }
```
Anything with `lock`/`unlock` (BasicLockable) works with `std::lock_guard`; add `try_lock` (Lockable) and it
works with `std::scoped_lock` and `std::unique_lock` too.

A spinlock burns a core while it waits, so it only pays off for critical sections of a few instructions when
there are spare cores. Otherwise the thread holding the lock may be descheduled while the others spin
uselessly. `std::mutex` spins briefly and then sleeps - it is the right default. C++20 lets a spinlock sleep
too: `busy.wait(true)` in the loop and `busy.notify_one()` in `unlock`.

## Quirks
1. **`std::atomic<int> a = 0;` is fine, `a = a + 1` is not atomic** (load, add, store). Use `++a`, `a += 1` or
   `fetch_add`.
2. **Before C++20 `std::atomic_flag f;` was uninitialised** and needed `= ATOMIC_FLAG_INIT`. C++20 fixed that,
   and added `test()` (read without setting).
3. **Atomics cannot be copied or moved**, so a class containing one loses its default copy/move.
4. **`std::atomic<T>` works for any trivially copyable `T`**, but large ones silently use a hidden lock: check
   `is_lock_free()` / `is_always_lock_free`.
5. **Memory orders.** The default `seq_cst` is always correct. `acquire`/`release` for locks and `relaxed` for
   pure statistics counters are optimisations; say "I would start with the default and measure".
6. **Lock-free is not automatically faster**, and under heavy contention a CAS loop can retry a lot. It mainly
   buys you immunity from a thread being paused while holding a lock.
7. **`volatile` is not for threads** in C++. It does not make anything atomic.
8. **False sharing**: two atomics on one cache line (64 bytes) ping-pong between cores.
   `alignas(std::hardware_destructive_interference_size)` separates them.
