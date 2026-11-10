# Lesson: binary search without off-by-one errors

## One template to remember
Search for the **first position where a condition becomes true**, on a half-open range `[lo, hi)`:

```cpp
std::size_t lo = 0, hi = v.size();
while (lo < hi) {
    std::size_t mid = lo + (hi - lo) / 2;
    if (v[mid] < x) lo = mid + 1;     // condition false at mid: answer is to the right
    else hi = mid;                    // condition true at mid: answer is mid or to the left
}
return lo;                            // == hi
```
Invariant: everything left of `lo` fails the condition, everything from `hi` on satisfies it. The range shrinks
every step, so it ends in O(log n). This is exactly `std::lower_bound`; with `v[mid] <= x` it is `std::upper_bound`.

## The midpoint quirk
`(lo + hi) / 2` overflows when `lo + hi` exceeds the type's range - a bug that sat in standard libraries for
years. Write `lo + (hi - lo) / 2`, or use C++20 `std::midpoint(lo, hi)`, which is overflow-safe by definition.

## Use the library in real code
```cpp
auto it = std::lower_bound(v.begin(), v.end(), x);      // iterator; it - v.begin() is the index
auto [first, last] = std::equal_range(v.begin(), v.end(), x);   // last - first == count
```
In an interview you may be asked to write it by hand, then mention these.

## Binary search on the answer
`isqrt(n)` has no array, but the predicate "r * r <= n" is true for small `r` and false for large `r`: a sorted
sequence of true/false. Search for the last `true`. To avoid overflow in `mid * mid`, test `mid <= n / mid`.
When searching for the **last** true, take the upper middle (`lo + (hi - lo + 1) / 2`) or the loop can get stuck.

## Why not `std::sqrt`?
A `double` has 53 bits of precision; `long long` has 63. Near 10^18 the conversion rounds, and the result can be off by one.
