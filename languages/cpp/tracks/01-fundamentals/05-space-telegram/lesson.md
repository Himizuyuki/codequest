# Lesson: runs, and parsing numbers by hand

## Finding a run
A **run** is a maximal stretch of equal characters. Use two indices: `i` is where the run starts, `j`
walks forward while the character stays the same.

```cpp
for (std::size_t i = 0; i < s.size(); ) {
    std::size_t j = i;
    while (j < s.size() && s[j] == s[i]) ++j;   // s[i .. j) is one run
    out += s[i];
    out += std::to_string(j - i);               // its length
    i = j;                                      // jump to the next run
}
```
Note the loop has no `++i` in the header: you move `i` yourself to the end of the run. That pattern
(an inner loop that consumes a group) is common in parsers.

## Parsing a multi-digit number
Digits arrive one at a time. For `"12"`: read `1` -> n = 1; read `2` -> n = 1 * 10 + 2 = 12.

```cpp
int n = 0;
while (i < s.size() && std::isdigit(static_cast<unsigned char>(s[i])))
    n = n * 10 + (s[i++] - '0');
```
`s[i] - '0'` turns the character `'7'` into the integer 7, because digit characters are consecutive.

## Building the output efficiently
`out.append(n, ch)` adds `n` copies of `ch` in one call. Avoid `out = out + ...` inside a loop: it copies the
whole string each time, which makes the total O(n^2).

## Why the "letters only" rule?
If the input could contain digits, `"a11"` would be ambiguous (eleven `a`, or an `a` and `1`...). Real
formats escape such cases or use a different layout. Spotting ambiguity in a spec is a real skill.

## When RLE helps (and hurts)
`"aaaaaaaa"` -> `"a8"` saves space, but `"abcdef"` -> `"a1b1c1d1e1f1"` doubles it. Compression always
depends on the data.
