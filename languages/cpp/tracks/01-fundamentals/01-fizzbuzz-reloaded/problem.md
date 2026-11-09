# FizzBuzz Reloaded

Mission control is counting down to launch, and the old FizzBuzz console has
been upgraded with a third rule.

For every number `i` from `1` to `n` (inclusive) produce one message:

- if `i` is divisible by 3, it contains `Fizz`
- if `i` is divisible by 5, it contains `Buzz`
- if `i` is divisible by 7, it contains `Zap`
- the words are joined in that order (`Fizz`, then `Buzz`, then `Zap`)
- if none apply, the message is the number itself

## Signature

```cpp
std::vector<std::string> fizzbuzz_reloaded(int n);
```

## Examples

| n  | result                                  |
|----|-----------------------------------------|
| 0  | `{}`                                    |
| 5  | `{"1", "2", "Fizz", "4", "Buzz"}`       |
| 7  | last element is `"Zap"`                 |
| 21 | last element is `"FizzZap"`             |
| 105| last element is `"FizzBuzzZap"`         |

## Notes

- `n` is never negative.
- Target: O(n) time.
