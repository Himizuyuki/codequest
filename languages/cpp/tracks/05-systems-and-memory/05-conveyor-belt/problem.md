# Conveyor Belt (condition variables)

Packers put parcels on a conveyor belt, loaders take them off at the other end. The belt holds only so
many parcels: a packer facing a full belt waits, a loader facing an empty belt waits. Nobody spins in a
loop burning CPU - they sleep until something changes.

This is the **bounded blocking queue**, the classic producer/consumer interview question.

```cpp
class BoundedQueue {
public:
    explicit BoundedQueue(std::size_t capacity);   // capacity >= 1

    bool push(int value);
    std::optional<int> pop();
    void close();
    std::size_t size() const;
};
```

- **`push`** appends `value`. If the queue is full it **blocks** until there is room. Returns `true` once the
  value is in. If the queue is (or becomes, while waiting) closed, it returns `false` and the value is dropped.
- **`pop`** removes and returns the oldest value (FIFO). If the queue is empty it **blocks** until a value
  arrives. Once the queue is closed **and** empty it returns `std::nullopt`.
- **`close`** shuts the belt: no new values are accepted, values already inside can still be popped, and
  every thread blocked in `push` or `pop` wakes up. Closing twice is harmless.
- **`size`** is the number of values inside right now; it never exceeds the capacity.

All methods may be called from any number of threads.

## Example

```cpp
BoundedQueue q(2);
q.push(1); q.push(2);        // a third push would block here until someone pops
q.pop();                     // 1
q.close();
q.push(9);                   // false
q.pop();                     // 2   (still inside)
q.pop();                     // nullopt (closed and empty)
```

## Notes

- A `timeout` result means some thread slept forever: a missed notification, or a `close()` that did not
  wake everybody.
- No busy waiting (`while (full) {}` or sleeping in a loop). Use `std::condition_variable`.
