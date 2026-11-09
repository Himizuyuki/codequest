# Longest Streak (Sliding Window)

A DJ never wants to repeat a song within a streak. Given the playlist as a string (one character per song), find
the length of the **longest substring with no repeated characters**.

```cpp
int longest_unique_substring(std::string_view s);
```

A substring is a contiguous piece of the string.

## Examples

| input        | result | longest streak |
|--------------|--------|----------------|
| `"abcabcbb"` | 3      | `abc`          |
| `"bbbbb"`    | 1      | `b`            |
| `"pwwkew"`   | 3      | `wke`          |
| `"dvdf"`     | 3      | `vdf`          |
| `"abba"`     | 2      | `ab` or `ba`   |
| `""`         | 0      |                |

## Notes

- Characters are bytes (any value 0-255); case matters.
- Target: O(n) time, O(1) extra space (the alphabet size is fixed).
- A substring is not a subsequence: `"pwwkew"` -> `"pwke"` is not allowed.
