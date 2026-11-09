# Bracket Inspector

The compiler's intern has to check whether the brackets in a piece of code are balanced.

A string is **balanced** when every opening bracket `(`, `[`, `{` is closed by the matching
bracket `)`, `]`, `}` in the correct order. All other characters are ignored.

## Signature

```cpp
bool is_balanced(std::string_view s);
```

## Examples

| input          | result  |
|----------------|---------|
| `""`           | `true`  |
| `"()[]{}"`     | `true`  |
| `"{[()]}"`     | `true`  |
| `"(]"`         | `false` |
| `"([)]"`       | `false` |
| `"(("`         | `false` |
| `"))"`         | `false` |
| `"a(b)c"`      | `true`  |

## Notes

- Target: O(n) time, O(n) space.
- One test has two million characters: no recursion, and watch the performance.
