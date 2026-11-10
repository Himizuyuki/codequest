# Relay Race (taking turns)

`runners` threads share one baton. Each thread may only run its leg when the baton reaches it, and the
baton travels in a fixed circle: runner 0, then 1, ..., then `runners - 1`, then 0 again.

Threads start whenever the operating system feels like it. Your job is to force an order onto them.

```cpp
class Relay {
public:
    explicit Relay(int runners);                           // runners >= 1; runner 0 holds the baton first

    void run(int id, const std::function<void()>& leg);
};
```

**`run(id, leg)`** is called by runner `id` (`0 <= id < runners`), from its own thread:

1. it **blocks** until it is runner `id`'s turn,
2. calls `leg()`,
3. passes the baton to runner `(id + 1) % runners`, and returns.

So whatever the timing, the legs execute strictly in the order 0, 1, 2, ..., 0, 1, 2, ... and two legs never
run at the same time.

## Example

```cpp
Relay relay(3);
// three threads; thread i does:   for (lap = 0; lap < 2; ++lap) relay.run(i, [&] { log.push_back(i); });
// log is always 0 1 2 0 1 2 - even if thread 2 started first
```

## Notes

- This is the family of "print in order", "print odd/even with two threads", "ping-pong" and
  "multithreaded FizzBuzz" interview questions.
- No busy waiting. A `timeout` result means the baton got lost: a runner is asleep and nobody will wake it.
