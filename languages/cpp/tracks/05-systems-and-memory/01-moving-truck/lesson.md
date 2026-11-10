# Lesson: copy, move and the rule of five

## Why the defaults are wrong for a raw owner
The compiler's copy constructor copies each member: here, the **pointer**. Two `Buffer`s then point at the same
array, and both destructors call `delete[]` on it: a double free. If a class manages a resource by hand,
it needs its own destructor, copy constructor and copy assignment (the *rule of three*), plus move constructor
and move assignment (the *rule of five*).

## The five
```cpp
~Buffer() { delete[] data_; }

Buffer(const Buffer& o) : size_(o.size_), data_(o.size_ ? new int[o.size_] : nullptr) {
    std::copy(o.data_, o.data_ + o.size_, data_);                       // deep copy
}

Buffer(Buffer&& o) noexcept
    : size_(std::exchange(o.size_, 0)), data_(std::exchange(o.data_, nullptr)) {}   // steal

Buffer& operator=(const Buffer& o) {
    if (this != &o) { Buffer tmp(o); std::swap(size_, tmp.size_); std::swap(data_, tmp.data_); }   // copy-and-swap
    return *this;
}

Buffer& operator=(Buffer&& o) noexcept {
    if (this != &o) { delete[] data_; size_ = std::exchange(o.size_, 0); data_ = std::exchange(o.data_, nullptr); }
    return *this;
}
```
`std::exchange(x, v)` sets `x = v` and returns the old value: perfect for "take it and leave nothing behind".

## What `std::move` really does
Nothing at run time. `std::move(x)` is a cast to an rvalue reference (`Buffer&&`), which makes overload
resolution pick the move constructor. The moving is done by *your* constructor.

## Quirks
1. **A moved-from object is still alive.** Its destructor will run, so leave it in a valid state (here: empty).
   Using it afterwards is allowed but its value is unspecified for standard types.
2. **`noexcept` matters.** `std::vector<Buffer>` only *moves* elements when it grows if the move constructor is
   `noexcept`; otherwise it copies them, to keep its strong exception guarantee. Forgetting `noexcept` silently
   costs performance.
3. **Declaring one special member suppresses others.** Declare a destructor or a copy operation and the compiler
   no longer generates the moves: "moving" then silently copies. Declare a move and the copies are deleted.
4. **`return local;` already moves** (or elides the copy entirely). Writing `return std::move(local);` *prevents*
   copy elision - a pessimisation.
5. **A named rvalue reference is an lvalue.** Inside `Buffer(Buffer&& o)`, `o` has a name, so `member(o.member)`
   copies; you must write `std::move(o.member)`.
6. **Self-assignment** (`a = a`, usually via aliases) must not destroy the data before copying it.

## The rule of zero
In real code, do not write any of this: hold a `std::vector<int>` or `std::unique_ptr<int[]>` and let the
compiler generate all five correctly. You write the five only when building such a resource-owning type -
and in interviews.
