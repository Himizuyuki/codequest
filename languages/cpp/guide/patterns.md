# Algorithm patterns: how to recognize them

Most interview problems are a small number of patterns in disguise. When you read a problem, ask which
clue it matches.

| Clue in the problem | Pattern | Typical cost |
|---|---|---|
| "find two numbers/items that ..." in an unsorted array | **Hash map** (remember what you have seen) | O(n) |
| Sorted input, pairs, or "from both ends" | **Two pointers** | O(n) |
| Longest/shortest *contiguous* substring or subarray with a condition | **Sliding window** | O(n) |
| Sum of a range, many range queries | **Prefix sums** | O(n) build, O(1) query |
| Sorted input, or "find the first position where ..." | **Binary search** (also on the answer) | O(log n) |
| Matching/nesting, "undo", next greater element | **Stack** | O(n) |
| Order of arrival matters, level by level, shortest path (unweighted) | **Queue / BFS** | O(V + E) |
| Explore all paths, connected components, "can I reach" | **DFS** | O(V + E) |
| k-th largest/smallest, top-k, merge k sorted lists, running median | **Heap** (`priority_queue`) | O(n log k) |
| Overlapping intervals | **Sort by start, then sweep** | O(n log n) |
| Count ways / min cost / "choose or skip" with overlapping subproblems | **Dynamic programming** | depends on the table size |
| Generate all combinations/permutations/subsets | **Backtracking** | exponential |
| Prefix lookup, autocomplete | **Trie** | O(length) |
| "Are these connected?" with merging groups | **Union-find** | ~O(1) amortized |

## How to use this
1. Write the brute force and its complexity.
2. Look at the table: which clue fits? Often the pattern turns O(n^2) into O(n) or O(n log n).
3. Check the pattern's assumption (sorted? non-negative? fixed alphabet?).
4. Code it, then test the edge cases: empty, one element, duplicates, extremes.

## Where you have seen them here
Hash map: Two Sum. Stack: Bracket Inspector. Two pointers: Palindrome Detective, Water Tank.
Sliding window: Longest Streak. Heap: Running Median.

Roadmap of all patterns: `ROADMAP.md`, track 03.
