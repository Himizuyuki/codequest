# Palindrome Detective

A palindrome reads the same forwards and backwards. The detective has two cases to crack.

## Case 1: the tidy palindrome

```cpp
bool is_palindrome(std::string_view s);
```
Ignore everything that is not a letter or a digit (ASCII), and ignore case. Return whether what
is left is a palindrome. If nothing is left, it counts as a palindrome.

| input                              | result  |
|------------------------------------|---------|
| `"A man, a plan, a canal: Panama"` | `true`  |
| `"race a car"`                     | `false` |
| `"No 'x' in Nixon"`                | `true`  |
| `"0P"`                             | `false` |
| `""` or `".,"`                     | `true`  |

## Case 2: the almost palindrome

```cpp
bool almost_palindrome(std::string_view s);
```
Here the string is taken **exactly as given** (no ignoring, case matters). Return `true` if the
string is a palindrome after deleting **at most one** character.

| input      | result  | why                      |
|------------|---------|--------------------------|
| `"aba"`    | `true`  | already a palindrome     |
| `"abca"`   | `true`  | delete `b` or `c`        |
| `"abc"`    | `false` |                          |
| `"deeee"`  | `true`  | delete `d`               |

## Notes

- Target: O(n) time and O(1) extra space for both functions.
- One test has a million characters.
