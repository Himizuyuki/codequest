# Complexity (Big-O) in five minutes

Big-O says how the running time grows when the input size `n` grows. Interviewers
always ask for it; say it out loud for every solution.

| Notation   | Name         | Example                                   | n = 1,000,000 |
|------------|--------------|-------------------------------------------|---------------|
| O(1)       | constant     | `v[i]`, `unordered_map` lookup (average)  | 1 step        |
| O(log n)   | logarithmic  | binary search, `std::map` lookup          | ~20 steps     |
| O(n)       | linear       | one loop over the input                   | 1 million     |
| O(n log n) | linearithmic | `std::sort`                               | ~20 million   |
| O(n^2)     | quadratic    | two nested loops over the input           | 10^12 (too slow) |
| O(2^n)     | exponential  | all subsets                               | impossible    |

## Rules of thumb
- Drop constants and lower terms: `3n^2 + 5n + 2` is O(n^2).
- Sequential steps add (`O(n) + O(n log n)` = O(n log n)); nested steps multiply.
- A computer does roughly 10^8 - 10^9 simple operations per second. So n = 10^5 allows O(n log n)
  or even O(n^2) barely; n = 10^6 needs O(n) or O(n log n).
- Space complexity counts extra memory you allocate (a hash map of n items is O(n) space).

## STL costs to remember
| Operation | Cost |
|---|---|
| `vector::push_back` | amortized O(1) |
| `vector::insert/erase` in the middle | O(n) |
| `deque` push/pop at both ends | O(1) |
| `map`/`set` insert/find/erase | O(log n) |
| `unordered_map`/`unordered_set` insert/find/erase | O(1) average, O(n) worst |
| `priority_queue` push/pop | O(log n), top is O(1) |
| `std::sort` | O(n log n) |
| `string` `+=` one char | amortized O(1); `s = s + "x"` copies: O(n) |

More: https://www.bigocheatsheet.com/
