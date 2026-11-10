# Lesson: combining containers - the LRU cache

## What each operation needs
| need | best container |
|---|---|
| find a key fast | `std::unordered_map` - O(1) |
| keep entries ordered by last use, move one to the front, drop the last | a doubly linked list - O(1) |

No single standard container does both, so use both and make them point at each other.

## The design
```cpp
std::list<std::pair<int, int>> order_;                                  // (key, value), most recent at the front
std::unordered_map<int, std::list<std::pair<int, int>>::iterator> where_;   // key -> its node in the list
std::size_t capacity_;
```
- **get(key)**: look up the iterator; if found, move that node to the front and return its value.
- **put(key, value)**: if the key exists, update and move to the front. Otherwise, if full, evict
  `order_.back()` (erase its key from the map, then `pop_back`), then `emplace_front` and record `begin()`.

## The key C++ fact: iterator stability
Storing iterators is only legal because of the list's guarantee: **inserting or erasing other elements never
invalidates iterators to a list node**. A `vector` or `deque` iterator would dangle after the next insertion.
Know these rules; interviewers probe them:

| container | iterators invalidated by |
|---|---|
| `vector` | any reallocation (growth); erase invalidates from the erased position on |
| `deque` | any insertion; erase in the middle |
| `list`, `forward_list` | only erasing that element |
| `map`, `set` | only erasing that element |
| `unordered_map` | rehash invalidates iterators (but **not** pointers/references to elements) |

## `splice`: move a node without copying
```cpp
order_.splice(order_.begin(), order_, it);     // relink node `it` to the front, O(1)
```
No allocation, no copy, and `it` stays valid - so the map does not even need updating.

## Why the list stores the key too
On eviction you only have the list's last node; you need its key to erase the map entry.

## Follow-ups you may be asked
Thread safety (a mutex around both structures), time-based expiry (TTL), LFU instead of LRU, making it a
template `LRUCache<K, V>`, and memory overhead (two allocations per entry; an intrusive list avoids one).

## How to present it
1. Clarify: capacity, what counts as a use, what `get` returns on a miss.
2. Brute force and its cost.
3. The two requirements, the two containers, and how they are linked.
4. Code, then walk the example table by hand.
