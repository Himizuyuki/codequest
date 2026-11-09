# Lesson: `std::optional` and `std::from_chars` (C++17)

## The problem with "magic" error values
How does a function say "I have no answer"? Returning `-1` or `0` is ambiguous (`-1` can be a
valid result), exceptions are slow and heavy for *expected* failures, and output parameters are clumsy.

## `std::optional<T>`
A value that is either present or absent:

```cpp
#include <optional>

std::optional<int> find_even(const std::vector<int>& v) {
    for (int x : v) if (x % 2 == 0) return x;   // implicit conversion: present
    return std::nullopt;                          // absent
}

if (auto r = find_even(v)) {                      // true when it has a value
    std::cout << *r;                              // * (or .value()) gets the value
}
int fallback = find_even(v).value_or(-1);         // default if absent
```
`optional` stores the value inline - no heap allocation. It makes "might fail" part of the
function's signature, so callers cannot forget to handle it.

## `std::from_chars`
`<charconv>` parses numbers without exceptions, locale, or allocation:

```cpp
int value = 0;
const char* first = text.data();
const char* last  = first + text.size();
auto [ptr, ec] = std::from_chars(first, last, value);   // structured binding on the result
bool ok = (ec == std::errc{} && ptr == last);
```
- `ec == std::errc{}`: it parsed a number.
- `ec == std::errc::result_out_of_range`: the digits do not fit in `int`.
- `ptr` points just after the last character used. If `ptr != last`, there was junk after the number (`"12a"`).
- An empty string, `"-"` or `"abc"` gives `std::errc::invalid_argument`.
- It accepts `-` but not `+` and no leading spaces. Convenient: that is the spec here.

## Integer division can be undefined
`a / 0` is undefined behavior. So is `INT_MIN / -1`: the true result, 2147483648, does not fit in
`int`. Signed overflow is UB in C++, so check for it *before* dividing.

## Chaining optionals
```cpp
auto a = parse_int(x);
if (!a) return std::nullopt;
```
In C++23 `std::optional::and_then` / `transform` chain these steps; but plain `if (!a)` is fine and
reads well.
