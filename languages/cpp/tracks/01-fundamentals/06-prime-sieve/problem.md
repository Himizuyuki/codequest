# Prime Sieve

The vault's lock only accepts prime numbers. List them all.

```cpp
std::vector<int> primes_up_to(int n);
```

Return every prime `p` with `2 <= p <= n`, in increasing order. If `n < 2` (including negative
numbers) return an empty vector.

## Examples

| n   | result                |
|-----|-----------------------|
| 10  | `{2, 3, 5, 7}`        |
| 2   | `{2}`                 |
| 1   | `{}`                  |
| 100 | 25 primes, last is 97 |

## Notes

- One test asks for all primes up to 10,000,000 (there are 664,579).
- Target: O(n log log n) with the sieve of Eratosthenes.
