# Lesson: breadth-first search on a grid

## A grid is a graph
Each free cell is a node; two cells sharing a side are connected. "Fewest moves" is the shortest path in an
unweighted graph, and that is what **BFS** computes.

## Why BFS gives the shortest path
BFS explores in waves: first all cells at distance 1, then all at distance 2, and so on. The first time it
reaches a cell is therefore by a shortest route. A `std::queue` (first in, first out) produces exactly that order.

```cpp
std::vector<std::vector<int>> dist(rows, std::vector<int>(cols, -1));
std::queue<std::pair<int, int>> todo;
dist[sr][sc] = 0;
todo.push({sr, sc});
while (!todo.empty()) {
    auto [r, c] = todo.front();
    todo.pop();
    if (grid[r][c] == 'E') return dist[r][c];
    for (int d = 0; d < 4; ++d) {
        int nr = r + dr[d], nc = c + dc[d];
        if (nr < 0 || nr >= rows || nc < 0 || nc >= cols) continue;   // bounds FIRST
        if (grid[nr][nc] == '#' || dist[nr][nc] != -1) continue;
        dist[nr][nc] = dist[r][c] + 1;                                // mark when pushing
        todo.push({nr, nc});
    }
}
return -1;
```

## Details that matter
- **Mark on push.** If you mark on pop, a cell can be queued many times and the queue explodes.
- **Bounds before access.** `grid[-1][0]` is undefined behavior, not an exception.
- `queue::pop()` returns nothing: read `front()` first.
- Each cell is pushed once and looks at 4 neighbours: O(rows * cols) time and memory.

## BFS vs DFS
DFS (recursion or a stack) answers "is it reachable?" but its first path is usually not the shortest, and
recursion a million levels deep overflows the call stack. Weighted moves need Dijkstra (a `priority_queue`).
