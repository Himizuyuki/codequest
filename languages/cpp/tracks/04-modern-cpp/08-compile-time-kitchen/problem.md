# Compile-Time Kitchen (constexpr)

In this kitchen the dishes are cooked before the restaurant opens: the **compiler** runs your functions,
and the program only contains the results.

```cpp
constexpr long long fib(int n);                 // fib(0) = 0, fib(1) = 1, fib(n) = fib(n-1) + fib(n-2); 0 <= n <= 90
constexpr bool is_prime(int n);
template <std::size_t N> constexpr std::array<int, N> first_primes();   // the first N primes
constexpr int count_primes_below(int n);        // how many primes p with p < n
```

Every function must be usable in a constant expression: the tests store the results in `constexpr`
variables, which forces the compiler to evaluate your code.

## Examples

| expression | value |
|---|---|
| `fib(10)`, `fib(50)` | `55`, `12586269025` |
| `is_prime(97)`, `is_prime(1)`, `is_prime(-7)` | `true`, `false`, `false` |
| `first_primes<5>()` | `{2, 3, 5, 7, 11}` |
| `count_primes_below(100)` | `25` |

## Notes

- The compiler limits how much work a constant expression may do. A naive recursive `fib` will not compile for `n = 50`.
- `is_prime(2147483647)` is also tested (at run time): `d * d` must not overflow.
