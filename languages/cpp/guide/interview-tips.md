# Interview tips

A routine you can repeat for every problem (about 35-45 minutes in a real interview):

1. **Clarify** (2-3 min). Restate the problem. Ask about input sizes, duplicates, negative numbers,
   empty input, sorted or not, one answer or many.
2. **Examples** (2 min). Walk through a small example and one edge case by hand.
3. **Brute force first** (2 min). State the obvious solution and its complexity. It shows you
   understand, and it gives you something to improve.
4. **Optimize** (5 min). Ask what is repeated or wasted. Common unlocks: a hash map (remember
   what you saw), sorting, two pointers, a heap, binary search, dynamic programming.
5. **Say the complexity** (1 min) in time *and* space before you code.
6. **Code** (15 min). Meaningful names, small helper functions, `const&` for big parameters.
   Talk while you type.
7. **Test** (5 min). Run your examples by hand, then the edge cases: empty, one element,
   duplicates, negatives, maximum size, overflow.

## C++-specific things interviewers like to see
- `const&` parameters, `std::string_view` for read-only text, `auto` where the type is obvious.
- Range-for loops and structured bindings instead of index juggling.
- `std::sort`, `std::unordered_map`, `std::priority_queue` instead of hand-rolled versions.
- Awareness of integer overflow (`int` is 32-bit; use `long long` for sums), of `%` with
  negative numbers, and of invalidated iterators.
- Prefer `std::vector` + indices over raw pointers; no `new`/`delete` unless asked.

## If you are stuck
Say what you are thinking, try a smaller example, ask for a hint. Silence is worse than a wrong idea.
