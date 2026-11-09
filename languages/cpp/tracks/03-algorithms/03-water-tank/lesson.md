# Lesson: two pointers that shrink the search space

## Brute force first
```cpp
for (i...) for (j = i + 1...) best = max(best, min(h[i], h[j]) * (j - i));
```
Correct but O(n^2): with 1,000,000 walls that is 500 billion pairs. Say this out loud in an interview, then ask:
*can I rule out many pairs at once?*

## Start wide, shrink smartly
Put one pointer at each end: this is the widest possible tank. Compute its area. Now you must move one
pointer inward (otherwise nothing changes). Which one?

- The water level is the **shorter** wall. Suppose `h[left] < h[right]`.
- Any tank that keeps `left` and moves `right` inward is **narrower**, and its level is still capped by
  `h[left]` (or lower). So it can never beat the current one. Every pair involving this `left` and a smaller `right` is eliminated.
- Therefore `left` is "used up": move it inward.

```cpp
std::size_t i = 0, j = h.size() - 1;      // careful: guard empty input first!
while (i < j) {
    best = std::max(best, (long long)std::min(h[i], h[j]) * (j - i));
    if (h[i] < h[j]) ++i; else --j;       // discard the shorter wall
}
```
Each step discards a wall for good, so the loop runs at most n-1 times: **O(n)**.

## Why this is a "greedy" argument
You are not trying everything; you prove that the discarded choices cannot be optimal and drop them.
Being able to explain *why* the move is safe is what interviewers want to hear.

## Practical details
- `(long long)std::min(...) * (j - i)`: cast first, otherwise the multiplication happens in `int` and can overflow
  (here up to 10,000 * 1,000,000 = 10^10, far beyond the `int` limit).
- `j - i` is `std::size_t` (unsigned); mixing it with a signed `int` in a product is fine here because the values are
  non-negative, but be careful with `i - j` in other problems.
- With `h.size() == 0`, `h.size() - 1` wraps around to a huge number. Return early for fewer than two walls.

## The two-pointers family
Sorted two-sum, three-sum, removing duplicates in place, palindromes (the previous problem), merging sorted arrays.
Pattern list: `./learn guide patterns`.
