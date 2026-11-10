# Parallel Sum (jthread & atomic)

The counting house hires several clerks to add up the ledger at the same time. Two jobs: split work
across threads, and make a counter that survives being hit from all sides.

```cpp
long long parallel_sum(const std::vector<int>& values, unsigned threads);

class SafeCounter {
public:
    void increment();          // may be called from many threads at once
    long long value() const;
};
```

- **`parallel_sum`**: the sum of `values`, computed by `threads` worker threads (`threads >= 1`), each summing
  its own slice. It must be correct for any thread count, including more threads than elements.
- **`SafeCounter`**: after `n` calls to `increment()` in total, from any number of threads, `value()` is exactly `n`.

## Examples

```cpp
parallel_sum({1, 2, 3, 4, 5}, 2);   // 15
parallel_sum({}, 4);                // 0

SafeCounter c;                      // 8 threads x 200,000 increments
c.value();                          // 1600000, every time
```

## Notes

- The tests check results, and hammer the counter from 8 threads. A counter with a data race usually
  gives a wrong total there - but "usually" is the nature of data races: passing once proves nothing, so reason about it.
- Use `std::jthread` (C++20): it joins automatically.
