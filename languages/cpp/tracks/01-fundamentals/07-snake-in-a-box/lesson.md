# Lesson: 2D vectors and shrinking boundaries

## A grid in C++
```cpp
std::vector<std::vector<int>> grid = {{1, 2, 3}, {4, 5, 6}};
int rows = grid.size();          // 2
int cols = grid[0].size();       // 3 - only valid if rows > 0!
grid[r][c];                      // row first, then column
```
Always handle the empty grid before touching `grid[0]`.

## Boundaries instead of a "visited" table
Keep four ints: `top`, `bottom`, `left`, `right` describing the rectangle not eaten yet. One lap:

1. top row, left to right, then `++top`
2. right column, top to bottom, then `--right`
3. bottom row, right to left (only if `top <= bottom`), then `--bottom`
4. left column, bottom to top (only if `left <= right`), then `++left`

Loop while `top <= bottom && left <= right`. The two `if`s matter: with one row left, step 1 eats it, and
without the check step 3 would eat it again backwards.

## Why `int`, not `size_t`
`size_t` is unsigned: `0 - 1` becomes a huge number instead of -1, so `--bottom` on 0 or a loop
`for (size_t c = right; c >= left; --c)` with `left == 0` never ends. For indexes that count down, signed
integers (or C++20 `std::ssize(v)`) avoid the wrap-around.

## Test like an interviewer
1x1, one row, one column, empty, and a non-square grid. Those five catch almost every bug here.
