# Lesson: dynamic programming in one dimension

## When greedy fails
"Take the biggest coin that fits" works for euros and dollars, but not in general: coins `{1, 3, 4}`,
amount 6 - greedy takes 4, 1, 1 (three coins) while 3 + 3 uses two. When a locally best choice can be
globally wrong, you need to consider all choices... without redoing the same work.

## The recurrence
The last coin of an optimal solution is some coin `c`. What remains, `amount - c`, must itself be made
optimally. So:

```
best[0] = 0
best[a] = 1 + min(best[a - c])   over all coins c <= a
```
A pure recursive version recomputes the same amounts exponentially often. **Dynamic programming** stores
each answer once, in a table, and fills it from small amounts to large ones:

```cpp
const int INF = amount + 1;                 // more coins than could ever be needed
std::vector<int> best(amount + 1, INF);
best[0] = 0;
for (int a = 1; a <= amount; ++a)
    for (int c : coins)
        if (c <= a) best[a] = std::min(best[a], best[a - c] + 1);
return best[amount] == INF ? -1 : best[amount];
```

## Why `amount + 1` and not `INT_MAX`
`INT_MAX + 1` overflows (undefined behavior). A sentinel that is "too big to be real but safe to add 1 to"
avoids the issue.

## The DP recipe
1. Define the state in words ("best[a] = fewest coins for amount a").
2. Write the recurrence and the base case.
3. Choose the fill order so needed answers are already computed.
4. State the complexity: number of states x work per state.

## Next steps
Counting the number of ways (not the minimum), 0/1 knapsack, longest common subsequence (a 2-D table).
