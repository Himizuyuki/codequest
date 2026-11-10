# Ticket Booth (compare-exchange, call_once, spinlock)

Three small classes, three classic race conditions. This time the tools are **atomics**, not mutexes.

```cpp
class TicketBooth {
public:
    explicit TicketBooth(int tickets);     // tickets >= 0
    bool try_buy();
    int remaining() const;
};

class Lazy {
public:
    explicit Lazy(std::function<int()> make);
    int get();
};

class SpinLock {
public:
    void lock();
    bool try_lock();
    void unlock();
};
```

- **`TicketBooth::try_buy`** sells one ticket and returns `true`, or returns `false` when none are left. However
  many threads call it, the booth never sells more tickets than it had, and **`remaining()`** is never
  observed below zero - not even for an instant. *Do it without a mutex.*
- **`Lazy::get`** returns `make()`'s result. `make` is slow and must be called **exactly once**, on the first
  `get()` - not in the constructor, and not twice when several threads call `get()` at the same moment.
  Every caller gets the same value.
- **`SpinLock`** is a mutex built from a single `std::atomic_flag`: `lock()` spins until it gets the lock,
  `try_lock()` takes it if free and reports whether it did, `unlock()` releases it. It must work with
  `std::lock_guard<SpinLock>`.

## Examples

```cpp
TicketBooth booth(2);
booth.try_buy();     // true
booth.try_buy();     // true
booth.try_buy();     // false
booth.remaining();   // 0

Lazy config([] { return load_config(); });   // nothing loaded yet
config.get();                                 // loads now
config.get();                                 // same value, no second load

SpinLock s;
{ std::lock_guard lock(s);  /* critical section */ }
```

## Notes

- The tests line threads up behind a `std::latch` and release them together, to make collisions likely.
  They still cannot prove the absence of a race - only your reasoning can.
