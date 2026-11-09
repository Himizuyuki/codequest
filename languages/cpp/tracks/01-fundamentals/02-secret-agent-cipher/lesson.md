# Lesson: characters are numbers, and `%` has a trap

## `char` is a small integer
`'a'` is 97, `'z'` is 122, `'A'` is 65. So the position of a letter in the alphabet is
`ch - 'a'` (0 for `a`, 25 for `z`). To shift and come back to a letter:

```cpp
char shifted = 'a' + (ch - 'a' + k) % 26;
```
Do the same with `'A'` for capitals. Anything that is neither is left alone.

## Wrap-around with modulo
Going past `z` must wrap to `a`: that is exactly "remainder after dividing by 26".

## The trap: `%` with negative numbers
In C++ the result of `%` takes the sign of the left operand:

```cpp
 7 % 26  ==  7
-1 % 26  == -1     // not 25!
```
A negative index would walk off the alphabet. The standard fix to get a result in `[0, 25]`:

```cpp
int k = ((shift % 26) + 26) % 26;
```
`shift % 26` is in `[-25, 25]`; adding 26 makes it positive; the outer `% 26` folds `26` back to `0`.

## Why reduce `shift` first?
`ch - 'a' + shift` can overflow `int` when `shift` is near `INT_MAX` - and signed overflow is
undefined behavior in C++. Reducing the shift to `0..25` first makes the arithmetic safe.
(Note `-shift` for `INT_MIN` overflows too - another reason to avoid it.)

## Modifying a string in place
```cpp
std::string out(text);          // copy
for (char& ch : out) { ... }    // the & lets you modify each character
```
