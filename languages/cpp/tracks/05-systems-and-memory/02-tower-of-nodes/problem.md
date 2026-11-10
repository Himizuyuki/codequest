# Tower of Nodes (unique_ptr)

Build a stack as a singly linked list where each node **owns** the node below it through a
`std::unique_ptr`. No `new`, no `delete`, no leaks - ownership does the cleanup.

```cpp
class Stack {
public:
    void push(int value);
    int pop();                  // removes and returns the top; throws std::out_of_range if empty
    int top() const;            // returns the top; throws std::out_of_range if empty
    std::size_t size() const;
    bool empty() const;
    ~Stack();
};
```

The skeleton in `solution.cpp` already declares:

```cpp
struct Node { int value; std::unique_ptr<Node> next; };
std::unique_ptr<Node> head_;
std::size_t size_ = 0;
```
Keep that representation.

## Example

```cpp
Stack s;
s.push(1); s.push(2); s.push(3);
s.top();   // 3
s.pop();   // 3
s.pop();   // 2
s.size();  // 1
```

## The catch

One test pushes **two million** values and then lets the stack go out of scope without popping. A stack
whose destructor is left to the compiler crashes there. Find out why, and fix it.
