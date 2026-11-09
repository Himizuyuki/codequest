# Word Frequency

The library's gossip column wants to know which words people repeat the most.
Return the `k` most frequent words in a piece of text.

## Rules

- A **word** is a maximal run of ASCII letters (`a-z`, `A-Z`). Everything else
  (spaces, digits, punctuation, apostrophes) separates words, so `it's` is two
  words: `it` and `s`.
- Words are compared **case-insensitively** and reported in lowercase.
- Sort by count, highest first. Ties are broken alphabetically (ascending).
- Return at most `k` entries (fewer if there are not enough distinct words).

## Signature

```cpp
std::vector<std::pair<std::string, int>> top_words(std::string_view text, std::size_t k);
```

## Example

```
text = "To be, or not to be: that is the question."
k    = 3
=> {{"be", 2}, {"to", 2}, {"is", 1}}
```

## Notes

- Target: O(n + d log d) where `d` is the number of distinct words.
