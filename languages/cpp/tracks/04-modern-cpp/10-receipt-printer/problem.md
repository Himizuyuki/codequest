# Receipt Printer (std::format)

The café's receipt printer needs neatly aligned columns. C++20's `std::format` does it in one line,
type-safely - no `printf` format mismatches, no `<<` chains with `std::setw`.

```cpp
std::string receipt_line(std::string_view item, int qty, double unit_price);
std::string hex_byte(unsigned char b);
std::string percent(double ratio);
std::string pad_id(int id);
```

## `receipt_line`

Five pieces glued together:

| piece | format |
|---|---|
| item | left-aligned in 12 columns, **cut** to 12 characters if longer |
| quantity | right-aligned in 3 columns |
| ` x ` | literally |
| unit price | right-aligned in 8 columns, 2 decimals |
| ` = ` then total | total right-aligned in 9 columns, 2 decimals |

```
coffee        2 x     3.50 =      7.00
extra-large-  1 x     5.25 =      5.25
```

## The others

| call | result |
|---|---|
| `hex_byte(15)`, `hex_byte(255)`, `hex_byte(0)` | `"0x0f"`, `"0xff"`, `"0x00"` |
| `percent(0.256)`, `percent(1.0)` | `"25.6%"`, `"100.0%"` |
| `pad_id(42)`, `pad_id(1234567)` | `"000042"`, `"1234567"` |
| `pad_id(-42)` | `"-00042"` (the sign counts in the width) |

## Notes

- Needs `<format>`: g++ 13 or newer.
