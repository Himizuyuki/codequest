# Lesson: trade memory for time with a hash map

## Start with the brute force
Try every pair `(i, j)`:
```cpp
for (int i = 0; i < n; ++i)
    for (int j = i + 1; j < n; ++j)
        if (nums[i] + nums[j] == target) return {i, j};
```
Two nested loops over n elements = **O(n^2)** time, O(1) space. Fine for n = 1000; far too slow
for n = 1,000,000 (that is 500 billion checks). Always state this first in an interview.

## Ask: what work is repeated?
For each `nums[i]`, the inner loop *searches* for `target - nums[i]`. A search over an unsorted
array is O(n). A hash map answers "have I seen this value, and where?" in O(1) on average.

## The one-pass solution
Walk the array once. For each element `x` at index `i`:
1. Look for `target - x` in the map of values seen so far.
2. If found at index `j`, the answer is `{j, i}`.
3. Otherwise remember `x -> i` and continue.

Lookup **before** inserting, and the same element can never pair with itself. Duplicates like
`{3, 3}` work naturally: the first 3 is stored, the second 3 finds it.

```cpp
std::unordered_map<int, int> seen;          // value -> index
if (auto it = seen.find(target - x); it != seen.end()) { /* it->second is j */ }
seen.emplace(x, i);
```
`if (init; condition)` (C++17) keeps `it` local to the `if`.

## Complexity
Time **O(n)** (n average O(1) lookups), space **O(n)** (the map). You traded memory for speed:
this is the most common optimization pattern in interviews.

## Variations to try later
Two Sum on a *sorted* array (two pointers, O(1) space), Three Sum, count all pairs.
