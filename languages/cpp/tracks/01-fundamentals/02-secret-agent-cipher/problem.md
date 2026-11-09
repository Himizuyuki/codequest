# Secret Agent Cipher

Agent K slips coded notes to headquarters using a Caesar shift. Write the
machine that encodes (and, with a negative shift, decodes) them.

Shift every ASCII letter forward by `shift` places in the alphabet, wrapping
around from `z` to `a`. Keep the case of each letter. Leave every other
character (spaces, digits, punctuation) untouched.

## Signature

```cpp
std::string caesar(std::string_view text, int shift);
```

## Examples

| text            | shift | result          |
|-----------------|-------|-----------------|
| `"abc"`         | 1     | `"bcd"`         |
| `"xyz"`         | 3     | `"abc"`         |
| `"Hello, World!"` | 13  | `"Uryyb, Jbeyq!"` |
| `"abc"`         | -1    | `"zab"`         |

## Notes

- `shift` can be negative and can be any `int` - including `INT_MIN`.
- Decoding is just `caesar(text, -shift)`... careful with that when `shift == INT_MIN`!
