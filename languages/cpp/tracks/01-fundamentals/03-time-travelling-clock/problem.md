# Time-Travelling Clock (Roman Numerals)

A time machine from ancient Rome has a clock that only understands Roman numerals. Build the
converter in both directions.

## Roman numerals refresher

| I | V | X  | L  | C   | D   | M    |
|---|---|----|----|-----|-----|------|
| 1 | 5 | 10 | 50 | 100 | 500 | 1000 |

Symbols are written from largest to smallest and added up (`VIII` = 8). Six *subtractive*
pairs exist: `IV` = 4, `IX` = 9, `XL` = 40, `XC` = 90, `CD` = 400, `CM` = 900.

## Signatures

```cpp
std::string to_roman(int n);          // 1 <= n <= 3999
int from_roman(std::string_view s);   // s is a valid numeral in standard form
```

## Examples

| n    | numeral       |
|------|---------------|
| 4    | `IV`          |
| 58   | `LVIII`       |
| 1994 | `MCMXCIV`     |
| 3999 | `MMMCMXCIX`   |

## Notes

- Inputs are always valid; you do not need error handling.
- `from_roman(to_roman(n)) == n` for every `n` from 1 to 3999.
