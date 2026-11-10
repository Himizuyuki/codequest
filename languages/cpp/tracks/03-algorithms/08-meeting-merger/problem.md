# Meeting Merger (Intervals)

The office calendar is full of overlapping meetings. Merge them into the blocks of time during which the
room is busy.

```cpp
std::vector<std::pair<int, int>> merge_intervals(std::vector<std::pair<int, int>> intervals);
```

Each interval is `{start, end}` with `start <= end`, both ends included. Two intervals that overlap **or
touch** (`{1,2}` and `{2,3}`) are merged. Return the merged intervals sorted by start.

## Examples

| input | result |
|---|---|
| `{1,3},{2,6},{8,10},{15,18}` | `{1,6},{8,10},{15,18}` |
| `{1,4},{4,5}` | `{1,5}` |
| `{5,7},{1,2},{2,3}` | `{1,3},{5,7}` |
| `{1,10},{2,3},{4,5}` | `{1,10}` |

## Notes

- The input is not sorted and may be empty.
- Target: O(n log n). One test has 200,000 intervals.
