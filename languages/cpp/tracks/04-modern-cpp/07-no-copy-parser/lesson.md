# Lesson: non-owning views - `std::string_view` and `std::span`

## Two tiny structs
Both are just a pointer and a length. They do not own, allocate or copy anything.

| | views | header | since |
|---|---|---|---|
| `std::string_view` | read-only characters | `<string_view>` | C++17 |
| `std::span<T>` | any contiguous `T`s (`vector`, `std::array`, C array, part of one) | `<span>` | C++20 |

```cpp
long long sum(std::span<const int> values);     // one signature...
sum(my_vector); sum(my_std_array); sum(c_array); sum({ptr, n});   // ...every contiguous source
```
Pass views **by value**; they are as cheap as two integers. `span<const int>` is read-only; `span<int>` lets
you modify the elements (not resize).

## Shrinking is free
```cpp
sv.remove_prefix(2);  sv.remove_suffix(1);  sv.substr(pos, len);       // string_view
sp.first(3);  sp.last(2);  sp.subspan(offset, count);                   // span
```
All of these only adjust the pointer and length. `std::string::substr`, by contrast, allocates a new string.

## C++20 additions
`sv.starts_with("/")`, `sv.ends_with(".cpp")` (also on `std::string`), and `std::span` itself.
(`contains` for strings is C++23.)

## The quirks - all about lifetime
1. **Dangling.** A view must not outlive the data:
   ```cpp
   std::string_view bad() { std::string s = "temp"; return s; }       // dangling
   std::string_view v = std::string("temp");                          // dangling after the semicolon
   std::span<const int> sp = make_vector();                           // dangling too
   ```
   No error, no warning by default, just garbage later. Views are for **parameters** and short-lived locals;
   store a `std::string`/`std::vector` when you need to keep the data.
2. **Not null-terminated.** `sv.data()` may not end with `'\0'`: never pass it to `printf("%s")`, `std::stoi`,
   `fopen`... Use `std::from_chars(sv.data(), sv.data() + sv.size(), x)` or build a `std::string`.
3. **Growth invalidates.** `push_back` on the underlying vector/string may reallocate; every view into it is
   then dangling.
4. **`span` has no `==`** (it was removed late in C++20 because "same elements" vs "same memory" was
   ambiguous). Use `std::ranges::equal(a, b)`. `string_view` does have `==`, comparing characters.
5. **Unsigned sizes.** `sp.size() - 1` on an empty span wraps around; see the Integer Traps problem.
6. **`span<const int>` vs `const span<int>`**: the first protects the elements, the second only the view itself.

## Why interviewers care
"How would you avoid copies here?" is a standard follow-up, and views are the answer. Being able to explain
the lifetime rule is the other half.
