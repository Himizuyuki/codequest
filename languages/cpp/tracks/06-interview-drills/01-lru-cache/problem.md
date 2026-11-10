# LRU Cache

One of the most asked design questions. A cache holds at most `capacity` entries; when it is full, the
entry that was **least recently used** is thrown out to make room.

```cpp
class LRUCache {
public:
    explicit LRUCache(std::size_t capacity);    // capacity >= 1
    std::optional<int> get(int key);            // the value, or std::nullopt; counts as a use
    void put(int key, int value);               // insert or update; counts as a use
    std::size_t size() const;
};
```

- `get` on an existing key and `put` (new or existing key) both make that key the most recently used.
- `put` of a **new** key into a full cache first evicts the least recently used key.
- `put` of an existing key replaces its value and never evicts.

## Example (capacity 2)

| operation | result | cache, most recent first |
|---|---|---|
| `put(1, 10)` | | 1 |
| `put(2, 20)` | | 2, 1 |
| `get(1)` | 10 | 1, 2 |
| `put(3, 30)` | evicts 2 | 3, 1 |
| `get(2)` | nullopt | 3, 1 |
| `put(4, 40)` | evicts 1 | 4, 3 |
| `get(1)` | nullopt | |
| `get(3)`, `get(4)` | 30, 40 | |

## Notes

- Target: **O(1)** for `get` and `put`. One test does a million operations on a 50,000-entry cache.
- Treat it like an interview: say the brute force first (a vector scanned on each call, O(capacity) per
  operation), then explain why two containers are needed.
