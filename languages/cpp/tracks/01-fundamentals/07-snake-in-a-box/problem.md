# Snake in a Box (Spiral)

A snake enters a rectangular box at the top-left corner and coils clockwise towards the centre,
eating every number once. In which order does it eat them?

```cpp
std::vector<int> spiral(const std::vector<std::vector<int>>& grid);
```

Start at the top-left, go right, then down, then left, then up, spiralling inward.

## Examples

```
1 2 3
4 5 6      =>  1 2 3 6 9 8 7 4 5
7 8 9

1  2  3  4
5  6  7  8     =>  1 2 3 4 8 12 11 10 9 5 6 7
9 10 11 12
```

## Notes

- The grid is rectangular (all rows have the same length) but may be empty, a single row or a single column.
- Target: O(rows * cols), visiting each cell once.
