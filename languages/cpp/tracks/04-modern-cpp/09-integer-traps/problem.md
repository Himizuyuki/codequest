# Integer Traps

Six one-liners that people have got wrong for decades. Each has an obvious implementation that is
broken for some inputs, and a C++20 library function that is right.

```cpp
bool safe_less(int a, unsigned int b);
int midpoint(int a, int b);
bool is_power_of_two(unsigned int x);
int bits_set(unsigned int x);
unsigned int round_up_to_power_of_two(unsigned int x);
int last_index(const std::vector<int>& v);
```

| function | meaning | the trap |
|---|---|---|
| `safe_less` | is `a < b` *mathematically*? | `-1 < 1u` is `false` in C++ |
| `midpoint` | halfway between `a` and `b`; if that is not an integer, round towards `a` | `(a + b) / 2` overflows |
| `is_power_of_two` | exactly one bit set | `x & (x - 1)` says yes for 0 |
| `bits_set` | number of 1 bits | hand-written loops |
| `round_up_to_power_of_two` | smallest power of two `>= x` (`x <= 2^31`; 0 gives 1) | shifts that overflow |
| `last_index` | index of the last element, `-1` if empty | `v.size() - 1` wraps to 18446744073709551615 |

## Examples

| call | result |
|---|---|
| `safe_less(-1, 1u)` | `true` |
| `midpoint(1, 4)`, `midpoint(4, 1)` | `2`, `3` |
| `midpoint(2147483647, 2147483645)` | `2147483646` |
| `is_power_of_two(0)`, `is_power_of_two(64)` | `false`, `true` |
| `bits_set(255)` | `8` |
| `round_up_to_power_of_two(5)` | `8` |
| `last_index({})` | `-1` |
