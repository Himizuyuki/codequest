# Lesson: two indices walking inward

## The idea
A palindrome is symmetric: the first character must equal the last, the second must equal the
second to last, and so on. So keep **two positions**, one at each end, and move them towards each other.

```cpp
std::size_t i = 0, j = s.size();      // [i, j) is what is left to check
while (j - i >= 2) {
    if (s[i] != s[j - 1]) return false;
    ++i;
    --j;
}
return true;
```
This is the **two pointers** pattern (see `./learn guide patterns`). Time O(n), extra space O(1) -
no copy of the string needed.

## Skipping noise
For case 1, before comparing, move each side past characters that do not matter:

```cpp
while (i < j && !std::isalnum(static_cast<unsigned char>(s[i]))) ++i;
while (i < j && !std::isalnum(static_cast<unsigned char>(s[j - 1]))) --j;
```
Then compare `std::tolower(...)` of both. Mind the bounds (`i < j`) so you never walk past the other pointer.

## Why `unsigned char`?
`char` may be signed. `std::isalnum` and `std::tolower` require a value that fits `unsigned char`
(or `EOF`); passing a negative `char` (e.g. an accented letter in UTF-8) is undefined behavior.

## "At most one deletion"
On the first mismatch at `(i, j)` you cannot know which side is the culprit, but there are only
two candidates: delete `s[i]` (check `[i+1, j]`) or delete `s[j]` (check `[i, j-1]`). Each check is a
plain palindrome test of a range, so write a small helper:

```cpp
bool is_pal(std::string_view s, std::size_t i, std::size_t j);   // [i, j) exactly
```
Only the **first** mismatch needs this branching, so the total work stays O(n).

## Edge cases
Empty string, a single character, a string of only punctuation, and `"0P"` (digits and letters
must not be confused when you lowercase).
