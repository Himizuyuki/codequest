# Space Telegram (Run-Length Encoding)

Sending bytes across the solar system is expensive, so the station compresses its telegrams with
**run-length encoding**: every run of the same letter becomes the letter followed by how many times it repeats.

```
aaabccdddd  ->  a3b1c2d4
```

## Signatures

```cpp
std::string rle_encode(std::string_view s);
std::string rle_decode(std::string_view s);
```

## Rules

- Input to `rle_encode` contains **letters only** (`a-z`, `A-Z`), so digits in the encoded text always belong to a count.
- A run of one letter is still written with its count: `"a"` becomes `"a1"`.
- Counts can have several digits: twelve `x` become `x12`.
- `rle_decode` is the exact inverse: `rle_decode(rle_encode(s)) == s`. Its input is always valid
  (a letter followed by a positive count, repeated).

## Examples

| encode input   | encode output |
|----------------|---------------|
| `""`           | `""`          |
| `"a"`          | `"a1"`        |
| `"aaabccdddd"` | `"a3b1c2d4"`  |
| `"xxxxxxxxxxxx"` (12 x) | `"x12"` |

| decode input | decode output |
|--------------|---------------|
| `"a3b1"`     | `"aaab"`      |
| `"z10"`      | `"zzzzzzzzzz"`|

## Notes

- Target: O(n) time. One test has a million characters, so avoid repeated `s = s + x` copying.
