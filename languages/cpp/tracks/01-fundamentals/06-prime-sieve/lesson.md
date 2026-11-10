# Lesson: the sieve, nested loops, and two C++ traps

## The idea
Write down 2..n. Take the first number not crossed out (2): it is prime; cross out its multiples.
Take the next one not crossed out (3): prime; cross out its multiples. Repeat.

```cpp
std::vector<bool> composite(n + 1, false);
for (long long i = 2; i <= n; ++i) {
    if (composite[i]) continue;
    primes.push_back(i);
    for (long long j = i * i; j <= n; j += i) composite[j] = true;
}
```
Why start at `i * i`? Smaller multiples (`2i`, `3i`, ...) were already crossed out by smaller primes.

## Trap 1: `i * i` overflows
With `int i`, `i * i` overflows once `i > 46340`, and signed overflow is undefined behavior. The loop
variable is `long long` here for that reason.

## Trap 2: `std::vector<bool>` is not a normal vector
It packs 8 flags per byte, so `composite[i]` returns a small *proxy object*, not a `bool&`. Consequences:
`auto x = v[0];` gives a proxy (not a `bool`), and `bool* p = &v[0];` does not compile. It is perfect here
(10 million flags in 1.25 MB) but surprising in generic code.

## Complexity
Each number is crossed out once per prime factor: about O(n log log n), practically linear. Trial division
for each number would be O(n * sqrt(n)).
