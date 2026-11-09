# STL containers cheat sheet

Pick the container by the operations you need most.

| Need | Use | Notes |
|---|---|---|
| A list of things, fast access by index | `std::vector<T>` | The default choice. Contiguous memory is cache-friendly. |
| Push/pop at both ends | `std::deque<T>` | Also the base of `std::queue`. |
| LIFO (stack) | `std::stack<T>` or just a `vector` with `push_back`/`pop_back` | |
| FIFO (queue) | `std::queue<T>` | BFS uses this. |
| Always get the largest (or smallest) | `std::priority_queue<T>` | Max-heap by default; `priority_queue<T, vector<T>, greater<T>>` for min-heap. |
| key -> value, fast | `std::unordered_map<K,V>` | Average O(1). Keys need a hash (ints, strings are fine). |
| key -> value, sorted by key | `std::map<K,V>` | O(log n); lets you iterate in order and use `lower_bound`. |
| "Have I seen this?" | `std::unordered_set<T>` / `std::set<T>` | |
| Fixed-size array | `std::array<T,N>` | |
| A view of someone else's data | `std::span<T>`, `std::string_view` | No copy; do not outlive the data. |

## Snippets
```cpp
std::vector<int> v = {3, 1, 2};
std::sort(v.begin(), v.end());                       // ascending
std::sort(v.begin(), v.end(), std::greater<>());     // descending
std::sort(v.begin(), v.end(), [](int a, int b) { return a > b; });  // custom

std::unordered_map<std::string, int> count;
for (const auto& w : words) ++count[w];              // [] creates the entry with 0

if (auto it = count.find("hello"); it != count.end()) {
    use(it->second);                                  // found
}

for (const auto& [word, n] : count) { /* structured bindings, C++17 */ }

auto pos = std::lower_bound(v.begin(), v.end(), 2);  // binary search in a SORTED range
```

## Pitfalls
- `map[key]` **inserts** a default value if the key is missing. Use `find`/`contains` (C++20) to only look.
- Inserting into a `vector` can invalidate iterators/references to its elements.
- `unordered_map` iteration order is unspecified - never rely on it.
- Pass big containers as `const std::vector<T>&`, not by value, unless you need a copy.

Reference: https://en.cppreference.com/w/cpp/container
