# Coin Machine (Dynamic Programming)

The change machine has an unlimited supply of each coin and hates wasting metal: it must give the change
using as few coins as possible.

```cpp
int min_coins(const std::vector<int>& coins, int amount);
```

Return the minimum number of coins that add up to exactly `amount`, or `-1` if it cannot be done.

## Examples

| coins       | amount | result | how          |
|-------------|--------|--------|--------------|
| `{1, 2, 5}` | 11     | 3      | 5 + 5 + 1    |
| `{2}`       | 3      | -1     | impossible   |
| `{1, 3, 4}` | 6      | 2      | 3 + 3 (greedy would use 3 coins) |
| anything    | 0      | 0      | no coin needed |

## Notes

- Coin values are positive and distinct; `0 <= amount <= 100000`; at most 20 coins.
- Target: O(amount * number of coins) time, O(amount) memory.
