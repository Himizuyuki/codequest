# No-Copy Parser (span & string_view)

The log server handles gigabytes of text and cannot afford to copy any of it. Every function here
returns **views into the caller's data** - the tests check that your results point inside the original
buffer.

```cpp
std::string_view trim(std::string_view s);
std::vector<std::string_view> split(std::string_view s, char sep);
bool is_command(std::string_view line);
long long sum(std::span<const int> values);
std::span<const int> longest_positive_run(std::span<const int> values);
```

- **`trim`**: remove spaces and tabs from both ends.
- **`split`**: cut at every `sep`. Empty fields are kept; an empty input gives one empty field.
- **`is_command`**: after trimming, does the line start with `/`?
- **`sum`**: the sum of the values, whatever container they come from (vector, `std::array`, C array).
- **`longest_positive_run`**: the longest stretch of consecutive values `> 0` (the first one if several
  have the same length; an empty span if there is none).

## Examples

| call | result |
|---|---|
| `trim("  hi there \t")` | `"hi there"` |
| `split("a,b,,c", ',')` | `{"a", "b", "", "c"}` |
| `split("", ',')` | `{""}` |
| `is_command("   /help")` | `true` |
| `longest_positive_run({1, 2, -1, 3, 4, 5, 0, 6})` | the `{3, 4, 5}` inside the input |

## Notes

- Do not allocate strings or copy the ints: return sub-views.
