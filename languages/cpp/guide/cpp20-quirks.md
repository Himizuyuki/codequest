# C++20: what is new, and the quirks that come with it

A map of the C++20 features worth knowing for interviews, each with its sharp edge and the problem that
practises it. Compile with `-std=c++20` (g++ 13 or newer for everything below).

## Language

| Feature | In one line | The quirk | Practise |
|---|---|---|---|
| `operator<=>` | one operator generates `<`, `<=`, `>`, `>=`; defaulted also gives `==` | a hand-written `<=>` does **not** give `==`; members compare in declaration order | 4.4 |
| Concepts, `requires` | named compile-time constraints on templates | `bool` and `char` satisfy `std::integral`; a `requires` only checks that code compiles | 4.6 |
| `consteval`, `constinit` | must-run-at-compile-time functions; compile-time *initialised* globals | `constexpr` only *allows* compile time; UB in a constant expression is a compile error | 4.8 |
| `constexpr` `std::vector`/`std::string` | heap allocation inside constant expressions | the memory must be freed before the evaluation ends | 4.8 |
| Aggregate CTAD | `overloaded{lambda1, lambda2}` without a deduction guide | older code still carries the guide | 4.3 |
| Designated initializers | `Point p{.x = 1, .y = 2};` | must follow declaration order, no mixing with positional (stricter than C) | |
| Lambda changes | templated lambdas, default-constructible captureless lambdas | `[=]` no longer captures `this` implicitly (deprecated): write `[=, this]` | 4.2 |
| `[[likely]]`, `[[nodiscard("why")]]`, `[[no_unique_address]]` | attributes | hints only | |
| `using enum` | bring enumerators into scope | | |
| Range-for with initializer | `for (auto v = get(); auto& x : v)` | fixes the dangling temporary in `for (auto& x : get().items())` (itself fixed in C++23) | |
| `char8_t` | distinct type for UTF-8 | `u8"..."` literals changed type: old code assigning them to `const char*` breaks | |
| Two's complement | signed integers are guaranteed two's complement | signed **overflow is still UB** | 4.9 |
| Modules, coroutines | `import`, `co_await`/`co_yield` | tool support is uneven; C++20 has coroutines but no `std::generator` (C++23) | |

## Library

| Feature | In one line | The quirk | Practise |
|---|---|---|---|
| Ranges and views | `v \| filter \| transform \| take`, `std::ranges::sort(v, {}, proj)` | no `ranges::to` until C++23; views do not own and are lazy | 4.5 |
| `std::span` | pointer + length view of any contiguous data | dangles like a pointer; has no `==` | 4.7 |
| `starts_with` / `ends_with` | on `string` and `string_view` | `contains` is C++23 | 4.7 |
| `std::format` | type-safe `printf` | format string must be a constant; `uint8_t` is a number here but a character for `cout` | 4.10 |
| `std::erase` / `std::erase_if` | one-call removal for every container | replaces the erase-remove idiom | 2.5 |
| `contains()` | on `map`, `set`, `unordered_*` | no more `count(k) > 0` or `find(k) != end()` | |
| `<bit>` | `popcount`, `has_single_bit`, `bit_ceil`, `bit_cast` | unsigned types only | 4.9 |
| `std::cmp_less`..., `std::ssize`, `std::midpoint` | safe mixed comparisons, signed size, overflow-free middle | plain `-1 < 1u` is still false | 4.9, 3.5 |
| `<numbers>` | `std::numbers::pi` | finally no `M_PI` | 4.3 |
| `std::jthread`, `stop_token` | thread that joins itself and can be asked to stop | `std::thread` still terminates the program if not joined | 5.3, 5.5 |
| `std::atomic` waits, semaphores, `latch`, `barrier` | `atomic_flag` is finally initialised by default, and gains `test()` | 5.6, 5.7 |
| `std::source_location` | file/line without macros | | |
| `<chrono>` calendars and time zones | `2024y / March / 1` | library support arrived late | |
| `std::to_array`, `std::make_shared<T[]>`, `std::bind_front` | small helpers | | |

## Things that changed meaning in C++20 (code that compiled before may not now)
- Comparison rewriting: `a == b` may be evaluated as `b == a`; an asymmetric or non-`const` `operator==` can
  become ambiguous or recurse forever.
- Aggregates: a class with a *user-declared* constructor (even `= delete` or `= default`) is no longer an
  aggregate, so `T{}` may stop compiling.
- `u8` literals are `char8_t`, not `char`.
- New keywords: `concept`, `requires`, `consteval`, `constinit`, `co_await`, `co_yield`, `co_return`, `char8_t`.
- Implicit `this` capture by `[=]`, the comma in subscripts (`a[i, j]`), and compound assignment on `volatile`
  are deprecated.

## What is *not* in C++20 (people often think it is)
`std::print`/`println`, `std::expected`, `std::ranges::to`, `std::generator`, `std::mdspan`, `string::contains`,
`std::flat_map`, deducing `this`, `if consteval` - all C++23.

## Evergreen C++ quirks interviewers love
- Iterator invalidation (see the table in `./learn lesson 6.1`).
- Undefined behavior: signed overflow, out-of-bounds access, use after free/move misuse, data races, reading
  uninitialised variables, dereferencing `end()`.
- `std::vector<bool>` is a packed bitset with proxy references.
- Order of evaluation of function arguments is unspecified.
- Object slicing when copying a derived object into a base; destructors of polymorphic bases must be `virtual`.
- `std::map::operator[]` inserts missing keys.
- The most vexing parse: `Widget w();` declares a function. Use `Widget w;` or `Widget w{};`.
- `static` initialisation order across translation units is unspecified (`constinit` helps).
