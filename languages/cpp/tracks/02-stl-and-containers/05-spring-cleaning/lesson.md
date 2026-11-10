# Lesson: erasing without invalidating

## The bug everyone writes once
```cpp
for (auto it = v.begin(); it != v.end(); ++it)
    if (*it % 2 == 0) v.erase(it);        // BUG
```
`erase` on a vector shifts the following elements and **invalidates** `it`. Incrementing it afterwards is
undefined behavior (in practice: skipped elements or a crash). The same goes for erasing inside a range-for.
Even the corrected form (`it = v.erase(it)`) is O(n) per erase, so O(n^2) overall.

## Before C++20: the erase-remove idiom
```cpp
v.erase(std::remove_if(v.begin(), v.end(), pred), v.end());
```
`remove_if` does not remove anything: it moves the keepers to the front and returns where the leftovers
begin. `erase` then chops the tail. One pass, O(n). Forgetting the `erase` part is a famous bug.

## C++20: uniform erasure
```cpp
std::erase(v, value);                 // remove all elements equal to value
auto n = std::erase_if(v, pred);      // remove all matching, returns the count
std::erase_if(my_map, [](const auto& entry) { return entry.second < 0; });   // works for maps and sets too
```
One spelling for every container, and the right algorithm for each (the idiom above for vectors, node
removal for maps).

## Removing duplicates
```cpp
std::sort(v.begin(), v.end());
v.erase(std::unique(v.begin(), v.end()), v.end());
```
`std::unique` only collapses **adjacent** equal elements, which is why you sort first.

## Quirk: map iterators
Erasing from a `std::map` only invalidates the iterator of the erased node, so the pre-C++20 loop was
`it = m.erase(it)`. `std::erase_if` hides that.
