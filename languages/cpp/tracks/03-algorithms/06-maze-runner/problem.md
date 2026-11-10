# Maze Runner (BFS)

A robot must leave the maze using as few moves as possible.

```cpp
int shortest_path(const std::vector<std::string>& grid);
```

The maze is a rectangle of characters:

| char | meaning |
|------|---------|
| `S`  | start (exactly one) |
| `E`  | exit (exactly one) |
| `.`  | free cell |
| `#`  | wall |

The robot moves one cell up, down, left or right per move (no diagonals), never through walls or outside
the grid. Return the minimum number of moves from `S` to `E`, or `-1` if the exit cannot be reached.

## Examples

```
S#E
.#.      => 6   (down, down, right, right, up, up)
...

S#E      => -1
```

## Notes

- Target: O(rows * cols). One test is a 1000 x 1000 maze, so recursion (DFS) would overflow the call stack.
