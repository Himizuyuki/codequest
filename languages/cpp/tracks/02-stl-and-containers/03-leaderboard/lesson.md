# Lesson: sorting by several keys

## A comparator is a question
`std::sort(first, last, comp)` calls `comp(a, b)`, which must answer: **"should `a` come before `b`?"**

```cpp
std::sort(v.begin(), v.end(), [](const Player& a, const Player& b) {
    if (a.score != b.score) return a.score > b.score;       // higher score first
    if (a.time_ms != b.time_ms) return a.time_ms < b.time_ms;   // then faster first
    return a.name < b.name;                                  // then alphabetical
});
```
Read it as a cascade: the first field that differs decides; later fields only break ties.

## The `std::tie` shortcut
Tuples compare lexicographically (first element, then second, ...). `std::tie` makes a tuple of
*references* without copying:

```cpp
return std::tie(a.score, a.time_ms, a.name) < std::tie(b.score, b.time_ms, b.name);
```
That sorts everything ascending. To sort one field descending, swap `a` and `b` for that field only:

```cpp
return std::tie(b.score, a.time_ms, a.name) < std::tie(a.score, b.time_ms, b.name);
//             ^^^ descending       ascending  ascending
```
Convince yourself on paper with two players that differ only in score.

## The rule you must not break: strict weak ordering
A comparator must be consistent: `comp(a, a)` is always `false`, and if `comp(a, b)` is true then
`comp(b, a)` is false. Writing `<=` instead of `<` breaks this, and `std::sort` may then read out of bounds
or crash on large inputs. The big test in this problem is there to catch exactly that.

## `sort` vs `stable_sort`
`std::sort` may reorder elements that compare equal; `std::stable_sort` keeps their original order. You
need `stable_sort` when equal elements must keep a meaning from an earlier sort (e.g. "sort by name, then
stable-sort by score" gives score order with ties in name order). Here all three keys are compared, so plain `sort` is enough.

## Pass-by-value is a feature here
`rank` takes the vector **by value**: the caller's vector is copied once, and you are free to sort your copy and
`return` it (the compiler moves it out, no second copy).
