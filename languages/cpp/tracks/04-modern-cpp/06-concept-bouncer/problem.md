# Concept Bouncer

Templates used to accept anything and explode pages later. C++20 **concepts** put a bouncer at the door:
the template states what it needs, and the wrong type is refused immediately with a readable message.

## 1. `Number` and `average`

```cpp
template <typename T> concept Number = /* ... */;
template <Number T> double average(const std::vector<T>& values);
```
`Number` is satisfied by integer and floating-point types, but **not** by `bool`. `average` returns the
mean (0.0 for an empty vector) and must be rejected at compile time for non-numbers.

## 2. `HasName` and `greet`

```cpp
template <typename T> concept HasName = /* ... */;
std::string greet(const HasName auto& who);       // "Hello, <name>!"
```
`HasName` is satisfied by types with a `name()` member, callable on a const object, whose result converts
to `std::string`.

## 3. `describe`

```cpp
std::string describe(const auto& value);
```

| argument type | result |
|---|---|
| `bool` | `"boolean"` |
| any other integer type (including `char`!) | `"integer"` |
| floating point | `"floating"` |
| convertible to `std::string_view` (`"hi"`, `std::string`) | `"text"` |
| anything else | `"other"` |

## Examples

| expression | value |
|---|---|
| `Number<int>`, `Number<double>` | `true` |
| `Number<bool>`, `Number<std::string>` | `false` |
| `average(std::vector<int>{1, 2})` | `1.5` |
| `describe(42)`, `describe(true)`, `describe("hi")` | `"integer"`, `"boolean"`, `"text"` |

The starter's concepts are placeholders that accept everything.
