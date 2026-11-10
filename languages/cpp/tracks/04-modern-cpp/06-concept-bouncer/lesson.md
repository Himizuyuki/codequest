# Lesson: concepts and `requires` (C++20)

## A concept is a named compile-time predicate
```cpp
template <typename T>
concept Number = std::integral<T> || std::floating_point<T>;
```
`Number<int>` is just a `bool` known at compile time. `<concepts>` ships many: `std::integral`,
`std::floating_point`, `std::same_as<T, U>`, `std::convertible_to<From, To>`, `std::invocable<F, Args...>`,
`std::totally_ordered`...

## Four ways to constrain a template (all equivalent)
```cpp
template <Number T> T twice(T x);                       // 1. in the template header
template <typename T> requires Number<T> T twice(T x);  // 2. requires clause
template <typename T> T twice(T x) requires Number<T>;  // 3. trailing requires
auto twice(Number auto x);                              // 4. abbreviated function template
```
Calling `twice("hi")` now fails **at the call site** with "constraints not satisfied", instead of deep
inside the body.

## `requires` expressions: "this code must compile"
```cpp
template <typename T>
concept HasName = requires(const T& t) {
    { t.name() } -> std::convertible_to<std::string>;   // expression must be valid AND its type must fit
};
```
Other forms inside the braces: a plain expression (`t.size();`), a type (`typename T::value_type;`), a nested
check (`requires sizeof(T) <= 8;`).

## Quirks
1. **`bool` is an integral type.** So are `char`, `char8_t`, `wchar_t`. `std::integral<bool>` is `true`; exclude
   it explicitly if you mean "number". (`std::is_arithmetic`, `std::is_integral` behave the same.)
2. **`requires requires`** is legal and means "requires clause containing a requires expression":
   `template <typename T> requires requires(T t) { t.foo(); } void f(T);` Prefer naming a concept.
3. **A requires expression only checks that code *compiles*.** `requires(T a) { a + a; }` says nothing about
   what `+` returns unless you add `-> std::same_as<T>`. And a simple requirement `{ t.empty() };` is not
   evaluated: it is never "false", only ill-formed or not.
4. **Subsumption picks the most constrained overload**, but only when the constraints are built from the same
   *named concepts* (`A<T> && B<T>` beats `A<T>`). Two equivalent-looking raw expressions are ambiguous.
5. **Concepts check syntax, not meaning.** A type with a `name()` that formats the hard disk satisfies `HasName`.
6. **Concepts cannot be specialized**, unlike type traits.

## `if constexpr`: branch on a concept inside one function
```cpp
if constexpr (std::same_as<T, bool>) return "boolean";
else if constexpr (std::integral<T>) return "integer";
```
The discarded branches are not even instantiated, so each branch may use operations the other types lack.
Order matters: test `bool` before `integral`.
