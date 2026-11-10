# Lesson: sort first, then sweep

## Sorting creates structure
Comparing every interval with every other is O(n^2). After sorting by start, anything that overlaps the
block you are building must come **next** in the list, so one left-to-right pass is enough.

```cpp
std::sort(intervals.begin(), intervals.end());       // pairs compare by .first, then .second
std::vector<std::pair<int, int>> out;
for (const auto& [start, end] : intervals) {
    if (!out.empty() && start <= out.back().second)
        out.back().second = std::max(out.back().second, end);   // overlap: extend
    else
        out.push_back({start, end});                             // gap: new block
}
```

## Two details
- **`max`, not assignment.** A long interval can swallow a short one: `{1,10}` then `{2,3}`.
- **`<=` vs `<`.** Here touching intervals merge, so the test is `start <= current_end`. In a problem where
  `{1,2}` and `{2,3}` do not conflict (a meeting ending at 2 and another starting at 2), it would be `<`.
  Always ask the interviewer.

## Free comparisons
`std::pair` and `std::tuple` come with lexicographic `<`, so they sort without a comparator. Since C++20
that is implemented with a single `operator<=>` (see the Spaceship Sorter problem).

## The pattern
"Sort by one end, then sweep" also solves: minimum number of meeting rooms, insert an interval, removing
the fewest intervals to avoid overlaps, and many scheduling problems.
