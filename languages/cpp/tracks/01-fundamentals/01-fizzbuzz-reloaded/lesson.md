# Lesson: loops, `%`, and building strings

## The loop
```cpp
for (int i = 1; i <= n; ++i) {
    // runs for i = 1, 2, ..., n
}
```

## `%` (remainder)
`a % b` is the remainder of `a / b`. A number is divisible by 3 exactly when `i % 3 == 0`.

## Why "append" beats "check every combination"
The naive approach writes one `if` per combination: 3 and 5 and 7, 3 and 5, 3 and 7, 5 and 7...
That is 7 branches for 3 rules, and 15 for 4 rules. Instead build the answer piece by piece:

```cpp
std::string word;
if (i % 3 == 0) word += "Fizz";
if (i % 5 == 0) word += "Buzz";
// ...
```
Each rule is independent, so adding a rule is one more line. The order of the `if`s decides the
order of the words. If `word` is still empty, no rule matched, so use the number.

## Return a vector
A function can return a `std::vector<std::string>` by value - C++ moves it out, no copy
(this is called *return value optimization*). Use `out.push_back(x)` to append and
`out.reserve(n)` first if you know the final size.

## Try it
Before coding, write the expected output for `n = 15` on paper, then compare with your result.
