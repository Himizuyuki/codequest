# Lesson: let a table do the work

## Data beats branching
You could write 13 `if`s for the symbols, but a **table** of pairs is shorter and harder to get wrong:

```cpp
struct Symbol { int value; const char* text; };
constexpr Symbol table[] = {
    {1000, "M"}, {900, "CM"}, {500, "D"}, {400, "CD"}, {100, "C"}, {90, "XC"},
    {50, "L"}, {40, "XL"}, {10, "X"}, {9, "IX"}, {5, "V"}, {4, "IV"}, {1, "I"},
};
```
Including the subtractive pairs (`CM`, `IV`, ...) as their own entries is the trick: no special cases later.

## Greedy: always take the biggest piece that fits
```cpp
for (const auto& [value, text] : table)      // structured binding (C++17)
    while (n >= value) { out += text; n -= value; }
```
This is a *greedy* algorithm. It is correct here because every larger entry is at least as big as
anything the smaller entries can build. (Greedy does NOT work for every coin system - you will meet
that in the coin-change problem.)

## Parsing: look one symbol ahead
Map a character to a value with a small `switch`. Then scan left to right:
if the current value is smaller than the next one (`IV`: I < V), subtract it; otherwise add it.

```
MCMXCIV  ->  1000 + (1000-100) + (100-10) + (5-1) = 1994
```

## Habits worth building
- `constexpr` tables are computed at compile time and cost nothing at run time.
- Test the round trip: `from_roman(to_roman(n)) == n` over the whole range - the tests do that too.
