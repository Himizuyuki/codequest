# Lesson: integers bite - and the C++20 antidotes

## Trap 1: mixing signed and unsigned
```cpp
int a = -1;  unsigned b = 1;
a < b        // false!
```
The "usual arithmetic conversions" turn `a` into `unsigned` first: -1 becomes 4294967295. The same happens in
`for (int i = 0; i < v.size(); ++i)` (the compiler warns with `-Wall`) and in `v.size() - 1` on an empty
vector, which is a gigantic number, not -1.

**C++20:** `<utility>` has `std::cmp_less`, `cmp_greater`, `cmp_equal`, `cmp_less_equal`... which compare the
mathematical values, and `std::in_range<T>(x)` ("does x fit in a T?"). `std::ssize(v)` (in `<iterator>`) returns
the size as a **signed** number, so `std::ssize(v) - 1` is really -1 for an empty container.

## Trap 2: the average of two ints
`(a + b) / 2` overflows when `a + b` does not fit (undefined behavior for signed types). The classic fix
`a + (b - a) / 2` still overflows when the signs differ.

**C++20:** `std::midpoint(a, b)` in `<numeric>` never overflows and rounds towards `a`. (There is also
`std::lerp` for floating point.)

## Trap 3: bit tricks
`x & (x - 1) == 0` has two bugs: `==` binds tighter than `&`, and with parentheses it still returns true
for `x == 0`. Hand-written popcount loops are slow or wrong for the top bit.

**C++20:** `<bit>` works on unsigned types and usually compiles to a single CPU instruction:

| function | result |
|---|---|
| `std::popcount(x)` | number of 1 bits |
| `std::has_single_bit(x)` | is `x` a power of two (false for 0) |
| `std::bit_ceil(x)` / `std::bit_floor(x)` | next / previous power of two |
| `std::bit_width(x)` | bits needed to represent `x` |
| `std::countl_zero`, `std::countr_zero` | leading / trailing zero bits |
| `std::rotl`, `std::rotr` | rotations |
| `std::bit_cast<To>(from)` | reinterpret bytes without undefined behavior |
| `std::endian::native` | byte order of the machine |

They refuse signed arguments at compile time, on purpose.

## Trap 4 (fixed in C++20): what a negative number is
Since C++20 signed integers are **guaranteed two's complement**, so converting an out-of-range value to a signed
type is well-defined (modulo 2^N), and `-1 >> 1` is an arithmetic shift. But signed **overflow in arithmetic is
still undefined behavior** - the compiler may assume `x + 1 > x`.

## Other integer quirks worth knowing
- Integer promotion: `unsigned char a = 200, b = 100; a + b` is the `int` 300, not 44.
- `char` may be signed or unsigned depending on the platform.
- `-7 / 2 == -3` and `-7 % 2 == -1` (division truncates toward zero).
- Shifting by >= the width of the type is undefined.
- `std::abs(INT_MIN)` is undefined (there is no +2147483648 in an `int`).
