# Lesson: three-way comparison (C++20)

## One operator, six comparisons
`a <=> b` answers "less, equal or greater?" in one go. The result is not an `int` but a *comparison
category* object that you compare with the literal `0`:

```cpp
auto c = a <=> b;
if (c < 0)  ... // a < b
if (c == 0) ... // equivalent
if (c > 0)  ... // a > b
```
When a type has `<=>`, the compiler *rewrites* `a < b` as `(a <=> b) < 0`, and likewise for `<=`, `>`, `>=`.

## Defaulting
```cpp
struct Date {
    int year, month, day;
    auto operator<=>(const Date&) const = default;
};
```
This compares the members **in declaration order**, lexicographically, and also gives you a defaulted
`operator==`. All six operators from one line.

### Quirk 1: member order is the comparison order
Declare `day` before `year` and your dates sort by day first. The bug is invisible in the comparison
code because there is none.

### Quirk 2: a custom `<=>` does not give you `==`
If you *write* `operator<=>` yourself, `==` and `!=` are **not** generated (equality can usually be done
faster than ordering, e.g. by comparing sizes first, so the language wants you to decide). `a == b`
simply fails to compile until you add `operator==`. `!=` is then rewritten from `==`.

### Quirk 3: the categories
| Category | Meaning | Example |
|---|---|---|
| `std::strong_ordering` | equal means indistinguishable | `int`, `Date` |
| `std::weak_ordering` | equivalent values may differ | case-insensitive strings: `"a"` vs `"A"` |
| `std::partial_ordering` | some values are unordered | `double` (because of NaN) |

`strong` converts to `weak` converts to `partial`, never the other way. A defaulted `<=>` returning `auto`
picks the weakest category among the members - add a `double` member and the type becomes partially ordered.

### Quirk 4: rewritten candidates
`a == b` may also be tried as `b == a`, so a mixed comparison like `Money == int` only needs one
operator. Occasionally old code with odd `operator==` signatures becomes ambiguous in C++20.

## Writing one by hand
```cpp
std::weak_ordering operator<=>(const CaseInsensitive& o) const {
    // compare char by char: if (a != b) return a <=> b;
    return text.size() <=> o.text.size();
}
bool operator==(const CaseInsensitive& o) const { return (*this <=> o) == 0; }
```
Helpers: `std::is_lt(c)`, `std::is_eq(c)`, `std::lexicographical_compare_three_way`.
