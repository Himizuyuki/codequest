# Strings and characters

## `std::string` vs `std::string_view`
- `std::string` **owns** its characters (it can grow, you can modify it).
- `std::string_view` (C++17) is a cheap, read-only *window* onto characters owned by something
  else - no copy. Use it for function parameters that only read text:
  `bool is_palindrome(std::string_view s)`.
- Never keep a `string_view` after its source string is gone (dangling view).

## Characters
- `char` is a small integer: `'a' == 97`, `'A' == 65`, `'0' == 48`. So `ch - 'a'` is the letter's
  index 0..25, and `ch - '0'` converts a digit char to its value.
- `<cctype>`: `std::isalpha`, `std::isdigit`, `std::isalnum`, `std::tolower`, `std::toupper`.
  They take an `int` that must be representable as `unsigned char`:
  `std::isalpha(static_cast<unsigned char>(ch))`.

## Building strings
```cpp
std::string s;
s += "abc";            // append, amortized O(1) per character
s.push_back('d');
s.reserve(1000);       // avoid reallocations if you know the size
std::string t = std::to_string(42);   // int -> string
```
Avoid `s = s + x` in a loop: it creates a temporary copy every time (O(n^2) overall).

## Numbers from text
```cpp
#include <charconv>
int value = 0;
auto [ptr, ec] = std::from_chars(text.data(), text.data() + text.size(), value);
if (ec == std::errc{} && ptr == text.data() + text.size()) { /* the whole text was a valid int */ }
```
`from_chars` never throws, never allocates and reports overflow via `ec`. (`std::stoi` throws.)

## Useful operations
`s.substr(pos, len)`, `s.find("x")` (returns `std::string::npos` if absent), `s.size()`,
`s.empty()`, `std::reverse(s.begin(), s.end())`, `s == other`, `s < other` (lexicographic).

Reference: https://en.cppreference.com/w/cpp/string
