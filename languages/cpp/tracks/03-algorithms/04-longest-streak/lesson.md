# Lesson: the sliding window

## The pattern
Many "best contiguous piece" problems fit a **window** `[start, i]` over the array or string:
- grow it by moving the right end `i` forward one step at a time;
- when the window breaks the rule (here: it has a repeat), shrink it from the left until it is valid again;
- record the best window seen.

Both ends only move forward, so the total work is O(n) even though there is a loop inside the loop (or, as
here, not even an inner loop).

## Applying it
Keep, for each character, the **last index** where it appeared. For each position `i`:

```cpp
unsigned char c = s[i];
if (last[c] >= start) start = last[c] + 1;   // c is already inside the window: jump past its old copy
last[c] = i;
best = std::max(best, i - start + 1);        // window length
```
`last` can be `std::array<int, 256>` filled with `-1`: a tiny, fast "map" from a byte to an index.

## The trap: `"abba"`
At the second `b` (index 2) the window becomes `[2, 2]`. At the final `a` (index 3), `last['a']` is `0`, which is
**before** `start`, so that `a` is no longer in the window. If you wrote `start = last[c] + 1` without the `>=`
check, `start` would move *backwards* to 1 and you would count `"ba"+"a"`... a window with a repeat. The
condition `last[c] >= start` is what keeps `start` monotone.

## Complexity
Time O(n): `i` visits each character once. Space O(1): the table has 256 entries regardless of n. For a generic
element type you would use `std::unordered_map` and say O(min(n, alphabet)).

## Recognize it
Clues: "longest/shortest *substring/subarray* such that...", a condition that is easy to maintain as you add on the right
and remove on the left (counts, sums, distinct elements). Related problems: max sum subarray of size k, minimum window
substring, longest substring with at most k distinct characters. See `./learn guide patterns`.
