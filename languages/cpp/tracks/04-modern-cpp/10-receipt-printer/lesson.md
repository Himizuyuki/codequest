# Lesson: `std::format` (C++20)

## Why it exists
`printf("%d", "oops")` compiles and crashes; `std::cout << std::setw(8) << std::fixed << std::setprecision(2)`
is verbose and leaves the stream modified. `std::format` (the standardised {fmt} library) is checked at
**compile time**, extensible, and returns a `std::string`.

```cpp
#include <format>
std::string s = std::format("{} has {} points", name, score);      // "ann has 42 points"
std::format("{1} before {0}", "a", "b");                           // positional: "b before a"
std::format("{{literal braces}}");                                 // "{literal braces}"
```

## The mini-language
`{:[fill][align][sign][#][0][width][.precision][type]}`

| spec | example | result |
|---|---|---|
| width, default alignment | `{:6}` with `42` / `"ab"` | `"    42"` / `"ab    "` (numbers right, text left) |
| `<` `>` `^` | `{:>6}`, `{:<6}`, `{:^6}` with `"ab"` | `"    ab"`, `"ab    "`, `"  ab  "` |
| fill | `{:*^7}` with `"hi"` | `"**hi***"` |
| zero padding | `{:05}` with `42` | `"00042"` |
| precision (floats) | `{:.2f}` with `3.14159` | `"3.14"` |
| precision (strings) | `{:.3}` with `"abcdef"` | `"abc"` - a maximum length |
| bases | `{:x}`, `{:X}`, `{:b}`, `{:o}` with `255` | `"ff"`, `"FF"`, `"11111111"`, `"377"` |
| `#` prefix | `{:#x}` with `255` | `"0xff"` |
| sign | `{:+}` with `5` | `"+5"` |

## Quirks
1. **The format string must be a compile-time constant.** `std::format(user_text, x)` does not compile; a wrong
   number or type of arguments is a compile error (that is the point). For a run-time string use
   `std::vformat(text, std::make_format_args(x))`, which throws `std::format_error` when it does not match.
2. **`char` types print as characters, `bool` as `true`/`false`.** `std::format("{}", 'A')` is `"A"`, and `{:d}`
   gives `65`. Small integer types like `unsigned char`/`uint8_t` are numbers for `std::format`, but characters
   for `std::cout` - a classic surprise when printing bytes. Convert to `unsigned` when in doubt.
3. **Width is a minimum, never a truncation** - except string precision. `{:3}` with `12345` prints all five digits.
4. **Zero padding counts the sign and prefix:** `{:06}` with `-42` is `"-00042"`.
5. **No locale by default** (unlike iostreams): `{:.2f}` always uses `.`; add `L` (`{:L}`) to opt in.
6. **Library support came late:** GCC 13, Clang 17 (libc++), MSVC 19.29. `std::print`/`std::println` are C++23.
7. Floats with plain `{}` print the *shortest* text that round-trips: `0.1 + 0.2` shows `0.30000000000000004`.

## Your own types
Specialise `std::formatter<T>` (often by inheriting from `std::formatter<std::string_view>`), and `T` works in
`std::format`, `std::print`, and logging libraries.
