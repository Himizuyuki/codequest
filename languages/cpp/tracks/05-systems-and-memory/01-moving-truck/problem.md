# Moving Truck (Rule of Five)

A `Buffer` owns a block of `int`s on the heap. When a class owns a raw resource, the compiler-generated
copy and destructor are wrong, and you must write the five special members yourself. This is the classic
"implement a class with correct copy and move" interview exercise.

```cpp
class Buffer {
public:
    explicit Buffer(std::size_t size);            // `size` ints, all zero
    Buffer(const Buffer& other);                  // deep copy
    Buffer(Buffer&& other) noexcept;              // steal; `other` becomes empty
    Buffer& operator=(const Buffer& other);
    Buffer& operator=(Buffer&& other) noexcept;
    ~Buffer();

    std::size_t size() const;
    int& at(std::size_t i);                       // throws std::out_of_range if i >= size()
    const int& at(std::size_t i) const;
    const int* data() const;                      // pointer to the first element, nullptr when empty
};
```

The skeleton is in `solution.cpp`, with the data members `size_` and `data_` already declared. Use
`new[]`/`delete[]` here - the point is to do by hand what `std::vector` does for you.

## Required behavior

- A **copy** has its own memory: changing one does not change the other.
- A **move** transfers the pointer (no allocation, no copying of elements) and leaves the source with
  `size() == 0` and `data() == nullptr`.
- Assigning a buffer to itself leaves it unchanged.
- No leaks and no double deletes.
