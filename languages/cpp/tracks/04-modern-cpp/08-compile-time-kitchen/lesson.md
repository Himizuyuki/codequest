# Lesson: `constexpr`, `consteval`, `constinit`

## `constexpr` = "may run at compile time"
```cpp
constexpr int square(int x) { return x * x; }

constexpr int a = square(12);     // MUST be computed by the compiler: a is a constant
int b = square(runtime_value);    // same function, ordinary run-time call
std::array<int, square(4)> arr;   // usable where a constant is required
static_assert(square(3) == 9);
```
A `constexpr` *variable* forces compile-time evaluation; a `constexpr` *function* merely allows it.

## What is allowed inside
C++11 allowed a single `return`. Today (C++14 to C++20) nearly everything: loops, local variables, `if`,
`switch`, `try` blocks, and in C++20 even `std::vector` and `std::string`, as long as every allocation is
freed before the evaluation ends ("transient allocation"). Results that must survive go in a `std::array`.

Not allowed: I/O, `reinterpret_cast`, uninitialized reads, and anything undefined.

## Quirk 1: UB becomes a compile error
In a constant expression, signed overflow, out-of-bounds access or a null dereference is a **compile-time
error** instead of silent undefined behavior. `constexpr` tests are therefore a free UB detector:
```cpp
constexpr int boom = std::numeric_limits<int>::max() + 1;   // error: overflow in constant expression
```

## Quirk 2: the compiler's patience is limited
There are caps on recursion depth and on the number of operations (GCC: `-fconstexpr-depth`,
`-fconstexpr-ops-limit`). An exponential algorithm that "just takes a while" at run time simply fails to
compile. Write the efficient version.

## Quirk 3: `constexpr` does not promise compile-time evaluation
`int x = fib(40);` with a non-constexpr `x` may be computed at run time. To *require* it:
- make the variable `constexpr`, or
- make the function **`consteval`** (C++20, an "immediate function"): every call must be a constant expression.
  ```cpp
  consteval int kb(int n) { return n * 1024; }
  int size = kb(4);          // fine, computed by the compiler
  int bad = kb(runtime_n);   // error
  ```

## Quirk 4: `constinit` is a different thing
`constinit int counter = 0;` (C++20) guarantees a global is *initialized* at compile time (avoiding the
"static initialization order fiasco") but the variable stays mutable. `constexpr` implies `const`; `constinit` does not.

## Also C++20
`std::is_constant_evaluated()` lets one function choose a compile-time friendly algorithm; `constexpr`
virtual functions, `constexpr` `std::sort` and most of `<algorithm>`, and lambdas are implicitly `constexpr` when possible.

## Why bother
Lookup tables with zero start-up cost, validated configuration, checks via `static_assert`, and array sizes
computed from real logic.
