# Ranges Pipeline

The factory's conveyor belt processes items in stages: filter, transform, take what you need. C++20
ranges let you write exactly that, with `|`. Five small jobs; each is one pipeline or one range algorithm.

```cpp
std::vector<int> squares_of_evens(const std::vector<int>& v, std::size_t limit);
long long sum_while_positive(const std::vector<int>& v);
std::vector<int> first_n_multiples(int k, std::size_t n);
std::vector<std::string> sort_by_length(std::vector<std::string> words);
bool has_long_word(const std::vector<std::string>& words, std::size_t len);
```

- **`squares_of_evens`**: the squares of the first `limit` even numbers of `v`, in order.
- **`sum_while_positive`**: the sum of the leading elements, stopping at the first one that is `<= 0`.
- **`first_n_multiples`**: `k, 2k, 3k, ...`, `n` of them.
- **`sort_by_length`**: shortest first; words of the same length in alphabetical order.
- **`has_long_word`**: is there a word with at least `len` characters?

## Examples

| call | result |
|---|---|
| `squares_of_evens({1,2,3,4,5,6,8}, 3)` | `{4, 16, 36}` |
| `sum_while_positive({3, 4, -1, 100})` | `7` |
| `first_n_multiples(7, 4)` | `{7, 14, 21, 28}` |
| `sort_by_length({"pear","fig","apple","kiwi"})` | `{"fig","kiwi","pear","apple"}` |
| `has_long_word({"a","abc"}, 3)` | `true` |

The tests can only check the results, but the point is to practise `<ranges>`: try not to write a
hand-made `if` inside a loop.
