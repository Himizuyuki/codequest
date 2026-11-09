# Anagram Detective

The detective has a pile of scrambled notes. Words made from the same letters belong to the
same case file. Group them.

Two words are **anagrams** if one is a rearrangement of the other's letters (`listen` / `silent`).

## Signature

```cpp
std::vector<std::vector<std::string>> group_anagrams(std::vector<std::string> words);
```

## Output format (so the answer is unique)

- Inside each group, words are sorted alphabetically (duplicates are kept).
- Groups are sorted by their first word, alphabetically.

## Example

```
{"eat", "tea", "tan", "ate", "nat", "bat"}
=> {{"ate", "eat", "tea"}, {"bat"}, {"nat", "tan"}}
```

## Notes

- Words use lowercase `a-z` only. The list may be empty.
- Target: O(total letters * log(word length) + n log n).
