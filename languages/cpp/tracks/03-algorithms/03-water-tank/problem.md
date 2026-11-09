# Water Tank (Two Pointers)

An engineer has a row of vertical walls of different heights, one unit apart. Picking any two walls
forms a tank: its **width** is the distance between the walls, and the water level is capped by the
**shorter** wall. Find the largest amount of water a tank can hold.

```cpp
long long max_water(const std::vector<int>& heights);
```

Area of a tank between positions `i < j` is `min(heights[i], heights[j]) * (j - i)`.

## Examples

| heights                       | result | best pair                       |
|-------------------------------|--------|---------------------------------|
| `{1, 8, 6, 2, 5, 4, 8, 3, 7}` | 49     | the `8` at index 1 and `7` at 8 |
| `{4, 3, 2, 1, 4}`             | 16     | the two `4`s                    |
| `{1, 2, 1}`                   | 2      | the two `1`s                    |
| `{1, 1}`                      | 1      |                                 |
| `{}` or `{5}`                 | 0      | fewer than two walls            |

## Notes

- Heights are non-negative `int`s (up to 10,000), at most 1,000,000 walls. The result can exceed 32 bits (up to about 10^10) - hence `long long`.
- Target: O(n) time, O(1) extra space. Checking every pair is O(n^2) and will time out.
