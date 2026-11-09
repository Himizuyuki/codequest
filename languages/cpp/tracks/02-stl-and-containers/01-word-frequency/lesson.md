# Lesson: counting with a hash map, sorting with a lambda

## The counting idiom
```cpp
std::unordered_map<std::string, int> counts;
++counts[word];
```
`counts[word]` creates the entry with value `0` if it is missing, then `++` makes it 1. Next
time it just increments. This one line is the most common use of a hash map in interviews.

An `unordered_map` finds a key in O(1) on average. A `std::map` would also work (O(log n) per
operation) and keeps keys sorted, but here we need to sort by *count*, not by word.

## Parsing words by hand
Walk the characters once, keeping a `std::string word` that you append to while you see letters.
When you see anything else, the current word (if non-empty) is finished: count it and clear it.
Do not forget the last word after the loop ends!

## Sorting pairs with a custom order
A map's elements are `std::pair<const std::string, int>`; copy them into a vector of
`std::pair<std::string, int>` to sort. `std::sort` takes a *comparator*: a function that says
"does `a` come before `b`?".

```cpp
std::sort(v.begin(), v.end(), [](const auto& a, const auto& b) {
    if (a.second != b.second) return a.second > b.second;   // higher count first
    return a.first < b.first;                                // then alphabetical
});
```
The `[](...) { ... }` is a **lambda**: an inline, nameless function. The comparator must be a
strict ordering (never return `true` for equal elements).

## Taking the first k
`if (v.size() > k) v.resize(k);` cuts the vector down. (A heap would be O(n log k) instead of
O(n log n), a nice follow-up when `k` is tiny.)

## Complexity to say out loud
Counting is O(n) for n characters; sorting the d distinct words is O(d log d).
