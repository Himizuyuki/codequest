# Lesson: the stack

## What a stack is
A **stack** is "last in, first out" (LIFO), like a pile of plates: you can only add or remove at
the top. In C++:

```cpp
std::stack<char> st;      // or a std::vector<char> using push_back / pop_back / back
st.push('(');
char top = st.top();      // look at the top
st.pop();                 // remove the top (returns nothing!)
st.empty();               // is it empty?
```
All operations are O(1). Calling `top()` or `pop()` on an empty stack is undefined behavior -
always check `empty()` first.

## Why a stack solves nesting problems
Brackets nest: the *last* bracket you opened is the *first* one that must be closed. That is
LIFO. So:

1. Opening bracket -> push it.
2. Closing bracket -> the stack must not be empty, and the top must be this bracket's opener.
   Pop it. If either check fails the string is not balanced.
3. At the end the stack must be empty - leftovers are brackets that were never closed.

## Matching opener
A tiny helper keeps the code tidy:
```cpp
char opener_of(char close) { return close == ')' ? '(' : close == ']' ? '[' : '{'; }
```

## Edge cases to test by hand
`""` (empty is balanced), `"("` (leftover), `")"` (closing with an empty stack), `"(]"` (wrong type).

## Same idea elsewhere
Evaluating expressions, undo/redo history, DFS without recursion, "next greater element",
parsing HTML tags.
