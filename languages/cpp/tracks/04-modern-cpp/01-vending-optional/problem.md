# Vending Machine (optional)

The vending machine reads prices as text and has to split the bill. Bad input must never crash it:
instead of exceptions or magic numbers, every function says "no valid answer" with
`std::optional` (C++17).

## Signatures

```cpp
std::optional<int> parse_int(std::string_view text);
std::optional<int> safe_div(int a, int b);
std::optional<int> divide_strings(std::string_view a, std::string_view b);
```

## Rules

**`parse_int`** returns the number if `text` is *entirely* a valid `int`, otherwise `std::nullopt`:
- optional leading `-`, then one or more digits, nothing else (no spaces, no `+`, no trailing characters)
- values outside the range of `int` are invalid (`"2147483648"` is `nullopt`, `"-2147483648"` is fine)

**`safe_div`** returns `a / b` (integer division) unless it is undefined: `nullopt` when `b == 0`,
and also for `INT_MIN / -1`, which overflows.

**`divide_strings`** parses both texts and divides them; `nullopt` if anything along the way failed.

## Examples

| call                          | result       |
|-------------------------------|--------------|
| `parse_int("42")`             | `42`         |
| `parse_int("-7")`             | `-7`         |
| `parse_int("")`, `("-")`, `("12a")`, `(" 5")`, `("+5")` | `nullopt` |
| `safe_div(7, 2)`              | `3`          |
| `safe_div(1, 0)`              | `nullopt`    |
| `divide_strings("100", "8")`  | `12`         |
| `divide_strings("100", "x")`  | `nullopt`    |
