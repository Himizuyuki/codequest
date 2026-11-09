# Running Median

A sensor sends numbers one at a time, and the dashboard must show the **median** of everything
received so far, after every single reading.

The median is the middle value of the sorted numbers; with an even count it is the average of the two
middle values.

```cpp
class RunningMedian {
public:
    void add(int x);          // receive one more number
    double median() const;    // median of all numbers so far
};
```

The class skeleton is in `solution.cpp`. Add whatever data members you need.

## Behavior

- `median()` on an empty stream throws `std::out_of_range`.
- Numbers may be negative and may repeat.

## Example

| add | numbers so far (sorted) | median |
|-----|-------------------------|--------|
| 5   | 5                       | 5      |
| 15  | 5, 15                   | 10     |
| 1   | 1, 5, 15                | 5      |
| 3   | 1, 3, 5, 15             | 4      |

## Notes

- Target: `add` in O(log n), `median` in O(1).
- One test streams 200,000 numbers; re-sorting every time would be far too slow.
