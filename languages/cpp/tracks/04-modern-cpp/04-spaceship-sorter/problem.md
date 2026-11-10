# Spaceship Sorter (operator<=>)

Before C++20, making a type fully comparable meant writing six operators (`==`, `!=`, `<`, `<=`, `>`, `>=`).
The "spaceship" operator `<=>` replaces them. Dock three ships.

## 1. `Date`: let the compiler do it

```cpp
struct Date { int year; int month; int day; };
```
Make `Date` comparable with all six operators: earlier dates are smaller. The starter has two wrong
placeholder operators; replace them with a single defaulted `operator<=>`.

## 2. `relation`

```cpp
std::string relation(const Date& a, const Date& b);   // "before", "same" or "after"
```
Is `a` before, the same as, or after `b`?

## 3. `CaseInsensitive`: write it yourself

```cpp
struct CaseInsensitive { std::string text; };
```
Compares like a dictionary that ignores case: `"Hello" == "HELLO"`, `"apple" < "Banana"`, and a prefix is
smaller than the longer word (`"app" < "apple"`). Implement `operator<=>` (returning `std::weak_ordering`)
and `operator==`.

## Examples

| expression | value |
|---|---|
| `Date{2024,5,1} < Date{2024,5,2}` | `true` |
| `Date{2023,12,31} < Date{2024,1,1}` | `true` |
| `relation({2024,1,1}, {2023,6,1})` | `"after"` |
| `CaseInsensitive{"Hello"} == CaseInsensitive{"HELLO"}` | `true` |
| `CaseInsensitive{"apple"} < CaseInsensitive{"Banana"}` | `true` |

Text is ASCII. The tests also sort vectors of both types.
