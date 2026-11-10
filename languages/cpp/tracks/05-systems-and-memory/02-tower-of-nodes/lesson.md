# Lesson: `std::unique_ptr` and ownership

## RAII in one sentence
An object acquires a resource in its constructor and releases it in its destructor, so cleanup happens
automatically on every path out of a scope - including exceptions. Smart pointers are RAII for heap memory.

## `std::unique_ptr<T>`: exactly one owner
```cpp
auto p = std::make_unique<Node>();     // allocate; never write `new`
p->value = 3;                          // use like a pointer
std::unique_ptr<Node> q = std::move(p);   // transfer ownership; p is now nullptr
// auto r = q;                         // does not compile: no copies
Node* raw = q.get();                   // non-owning observer (do not delete it)
q.reset();                             // destroy the node now
```
It is the same size as a raw pointer and has no run-time overhead. Deleting happens when the owner dies.
`std::shared_ptr` (several owners, reference counted) is for the rarer case of genuinely shared lifetime.

## A linked structure with owning links
```cpp
struct Node { int value; std::unique_ptr<Node> next; };
std::unique_ptr<Node> head_;

head_ = std::make_unique<Node>(Node{value, std::move(head_)});   // push
head_ = std::move(head_->next);                                   // pop: the old head is deleted
```
Every arrow in the picture is an owner, and each `std::move` in the code is a visible ownership transfer.

## The quirk: recursive destruction
With the compiler-generated destructor, destroying `head_` deletes node 1; node 1's destructor destroys its
`next`, deleting node 2; and so on. That is **one nested function call per node**. A million nodes need a
million stack frames, and the call stack (typically 8 MB) overflows: segmentation fault at scope exit, in code
you never wrote.

The fix is to unlink iteratively, so each node is destroyed with an empty `next`:
```cpp
~Stack() { while (head_) head_ = std::move(head_->next); }
```
The same problem affects `shared_ptr` lists, trees that are very deep, and recursive `variant` structures.

## More quirks
- Declaring the destructor suppresses the implicit **move** operations, and the `unique_ptr` member already
  deletes the copies: this `Stack` is neither copyable nor movable unless you add
  `Stack(Stack&&) noexcept = default;` etc. (rule of five).
- `unique_ptr<T>` needs the complete type of `T` where it is *destroyed*, which is why the pimpl idiom defines
  the destructor in the `.cpp` file.
- Pass `const T&` or `T*` to functions that only use the object; pass `std::unique_ptr<T>` by value to hand
  over ownership. Never `const std::unique_ptr<T>&` just to read.
- `make_unique` is exception-safe and avoids writing the type twice; `new` in application code is a smell.
