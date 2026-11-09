# Arcade Leaderboard

The arcade wants a leaderboard that is fair when scores tie.

```cpp
struct Player {
    std::string name;
    int score;
    int time_ms;     // how long the run took, in milliseconds
};

std::vector<Player> rank(std::vector<Player> players);
```

`Player` is already defined in `solution.cpp` - **do not change it**. Return the players ordered
from first place to last:

1. higher `score` first;
2. on equal scores, the **smaller** `time_ms` first (faster is better);
3. on equal score and time, `name` in alphabetical order.

## Example

```
{"ann", 10, 500}, {"bob", 30, 700}, {"cy", 30, 200}, {"dee", 30, 200}
=> cy, dee, bob, ann
```
`cy` and `dee` tie on score and time, so the name decides; both beat `bob` on time; `ann` has the lowest score.

## Notes

- Target: O(n log n). One test ranks 100,000 players.
- The function takes the vector **by value**, so you can sort it in place and return it.
