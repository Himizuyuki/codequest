# Lesson: group by a canonical key

## The pattern
"Group things that are equivalent" nearly always means: **compute a canonical key** such that
equivalent things get the *same* key, then put them in a map from key to list.

For anagrams the canonical key is the word with its letters sorted:

```
"eat" -> "aet"
"tea" -> "aet"      same key -> same group
"tan" -> "ant"
```
```cpp
std::string key = word;
std::sort(key.begin(), key.end());      // sorts the characters of the string
groups[key].push_back(word);            // groups is a std::map<std::string, std::vector<std::string>>
```

## `map` or `unordered_map`?
Either works. `std::map` keeps keys sorted, which is not needed here but is harmless.
`std::unordered_map` is O(1) per lookup on average. Since we sort the final groups ourselves,
`unordered_map` is the slightly faster choice; the output order is then set by your final sort.

## Finishing: a deterministic order
Hash maps iterate in an unspecified order, so make the output deterministic:
1. `std::sort` the words within each group,
2. `std::sort` the groups (vectors compare lexicographically, so `a.front() < b.front()` works,
   or just compare the vectors with `<`).

## Moving data instead of copying
When you build the result from the map, `std::move(entry.second)` hands the vector over without
copying every string:
```cpp
for (auto& [key, group] : groups) result.push_back(std::move(group));
```

## Alternative key
A frequency array of 26 counts also works as a key and avoids sorting (O(L) instead of
O(L log L) per word). Try it as a follow-up.
