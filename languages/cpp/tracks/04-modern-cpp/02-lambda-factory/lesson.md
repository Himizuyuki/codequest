# Lesson: lambdas and what they capture

## Anatomy
```cpp
auto add = [offset](int x) -> int { return x + offset; };
//         ^capture  ^params  ^return type (optional)
```
A lambda is an object of an unnamed class; captures are its data members; the body is its `operator()`.

## Capture modes
| Capture | Meaning |
|---|---|
| `[x]` | copy of `x`, made when the lambda is created |
| `[&x]` | reference to `x` - the lambda must not outlive `x` |
| `[=]` / `[&]` | everything used, by copy / by reference |
| `[n = start]`, `[p = std::move(ptr)]` | *init-capture*: a new member with any initial value (C++14) |

## Quirk 1: returning a lambda that captures by reference
```cpp
std::function<int()> broken() { int n = 0; return [&n] { return n++; }; }   // n is dead when called
```
Undefined behavior, and it often *seems* to work. Anything returned, stored or sent to another thread
captures **by value**.

## Quirk 2: by-value captures are const
`[n] { return n++; }` does not compile: `operator()` is `const`. Add `mutable` to allow changing the
lambda's own copy: `[n]() mutable { return n++; }`. The state lives inside the lambda object.

## Quirk 3: the loop variable
```cpp
for (int i = 0; i < n; ++i) out.push_back([&i](int x) { return x + i; });   // all share one dead i
```
Capture `[i]`: each lambda gets its own copy.

## Quirk 4 (C++20): `[=]` and `this`
In a member function `[=]` used to capture `this` silently, so "by copy" lambdas still dangled when the
object died. C++20 deprecates that: write `[=, this]` (pointer) or `[=, *this]` (a copy of the object).

## `std::function` vs `auto`
`auto f = [..]{..};` keeps the exact lambda type: zero overhead, can be inlined. `std::function<int(int)>`
can hold *any* callable with that signature (needed to return different lambdas or store them in a vector)
at the cost of an indirect call and possibly a heap allocation. Copying a `std::function` copies the
lambda inside, including its captured state.

## More C++20
Lambdas can be used in unevaluated contexts and be default-constructed when captureless, and generic
lambdas can be written with explicit template parameters: `[]<typename T>(std::vector<T> const& v) {...}`.
