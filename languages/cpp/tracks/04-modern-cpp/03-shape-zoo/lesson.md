# Lesson: `std::variant`, `std::visit` and the `overloaded` trick

## A type-safe union
```cpp
std::variant<int, std::string> v = 42;      // holds an int
v = std::string("hi");                      // now holds a string
std::holds_alternative<int>(v);             // false
std::get<std::string>(v);                   // "hi"; std::get<int>(v) would throw std::bad_variant_access
if (auto* p = std::get_if<int>(&v)) { ... } // pointer or nullptr, never throws
v.index();                                  // 1
```
The variant stores the value inline (no heap) and always knows which alternative is active.

## Visiting
`std::visit(f, v)` calls `f` with the active alternative. `f` must be callable with **every** alternative,
and each call must return the same type. That is the big win over `if`/`else` chains: add a fourth shape
and every `visit` that does not handle it stops compiling.

## The `overloaded` helper
```cpp
template <class... Ts> struct overloaded : Ts... { using Ts::operator()...; };

double area(const Shape& s) {
    return std::visit(overloaded{
        [](const Circle& c)   { return std::numbers::pi * c.r * c.r; },
        [](const Rect& r)     { return r.w * r.h; },
        [](const Triangle& t) { /* Heron */ return 0.0; },
    }, s);
}
```
`overloaded` inherits from all the lambdas and pulls in their call operators, producing one object with
three overloads.

**C++20 quirk:** in C++17 this needed an extra line, a *deduction guide*
(`template <class... Ts> overloaded(Ts...) -> overloaded<Ts...>;`). C++20 deduces template arguments for
aggregates, so the guide is no longer needed. You will see both versions in the wild.

## Alternative: one generic lambda
```cpp
std::visit([](const auto& x) {
    if constexpr (std::is_same_v<std::decay_t<decltype(x)>, Circle>) ...
}, s);
```

## variant vs virtual
Variant: closed set of types, values stored inline, no allocation, exhaustive checking, easy to add new
*operations*. Virtual functions: open set of types, easy to add new *types*. Interviewers like hearing that trade-off.

## C++20: `<numbers>`
`std::numbers::pi`, `e`, `sqrt2`... finally replace `M_PI` (never standard) and hand-typed constants.
