# Lambda Factory

The factory builds small functions on demand. Every function here **returns a function**, so what the
lambda captures, and how, decides whether it works or silently breaks.

```cpp
std::function<int()> make_counter(int start);
std::function<int(int)> make_multiplier(int k);
std::vector<std::function<int(int)>> make_adders(int n);
std::function<int(int)> compose(std::function<int(int)> f, std::function<int(int)> g);
int apply_n(const std::function<int(int)>& f, int times, int x);
```

- **`make_counter(start)`**: each call of the result returns `start`, then `start + 1`, ... Two counters are independent.
- **`make_multiplier(k)`**: the result maps `x` to `x * k`.
- **`make_adders(n)`**: a vector of `n` functions where `adders[i](x) == x + i`.
- **`compose(f, g)`**: the result maps `x` to `f(g(x))`.
- **`apply_n(f, times, x)`**: applies `f` to `x`, `times` times (`times == 0` returns `x`).

## Examples

```cpp
auto next = make_counter(5);   next(); // 5     next(); // 6
auto triple = make_multiplier(3);      triple(7); // 21
auto adders = make_adders(3);          adders[2](10); // 12
auto f = compose(make_multiplier(2), make_adders(4)[3]);   f(1); // (1 + 3) * 2 = 8
apply_n(make_multiplier(2), 10, 1); // 1024
```
