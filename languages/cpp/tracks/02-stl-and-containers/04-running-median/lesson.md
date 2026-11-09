# Lesson: two heaps share the work

## The naive options
- Keep a sorted `vector` and insert each number: finding the spot is O(log n) but shifting elements is O(n).
- Re-sort on every `median()`: O(n log n) per query.

For 200,000 numbers both are too slow. The trick: you never need the whole order, only the **middle**.

## Heaps in C++
A `std::priority_queue<T>` is a **max-heap**: `top()` is the largest element, `push`/`pop` are O(log n), `top` is O(1).
For a **min-heap** change the comparator:

```cpp
std::priority_queue<int> max_heap;                                        // largest on top
std::priority_queue<int, std::vector<int>, std::greater<>> min_heap;      // smallest on top
```

## Two heaps, one median
Keep the numbers split in two halves:
- `low`: a max-heap with the smaller half. Its top is the largest of the small numbers.
- `high`: a min-heap with the larger half. Its top is the smallest of the big numbers.

The median sits exactly between them: if `low` has one more element, it is `low.top()`; if the sizes are
equal it is the average of both tops.

## Adding a number
1. Put it in the right half: `x <= low.top()` goes to `low`, otherwise to `high` (when `low` is empty, `low`).
2. **Rebalance** so `low.size()` is `high.size()` or `high.size() + 1`: if `low` got too big, move its top to
   `high`; if `high` got bigger, move its top to `low`.

Each add does a constant number of heap operations: O(log n). `median()` only looks at the tops: O(1).

## Details that bite
- Average of two ints: write `(static_cast<double>(a) + b) / 2.0`. `(a + b) / 2` would be integer division
  and `a + b` can overflow `int`.
- `median()` is `const`, so it may call `top()` (a const function) but not `pop()`.
- Empty stream: `throw std::out_of_range("...")` from `<stdexcept>`.

## Same idea elsewhere
Median of a sliding window, "k-th smallest in a stream", scheduling with two priority levels.
