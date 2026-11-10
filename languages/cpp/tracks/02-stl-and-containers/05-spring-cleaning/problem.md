# Spring Cleaning (Erasing Safely)

Removing things from a container while walking through it is the classic way to shoot yourself in
the foot in C++. Three chores, three clean solutions.

```cpp
void remove_multiples(std::vector<int>& v, int k);
std::vector<int> sorted_unique(std::vector<int> v);
int evict_expired(std::map<std::string, int>& sessions, int now);
```

- **`remove_multiples`** removes every element divisible by `k` (`k != 0`; note `0` is divisible by
  everything), keeping the others in their original order.
- **`sorted_unique`** returns the distinct values in ascending order.
- **`evict_expired`**: `sessions` maps a user name to an expiry time. Remove every session whose expiry
  is `<= now` and return how many were removed.

## Examples

| call | result |
|---|---|
| `remove_multiples({1,2,3,4,5,6}, 2)` | `{1,3,5}` |
| `sorted_unique({3,1,3,2,1})` | `{1,2,3}` |
| `evict_expired({{"ann",5},{"bob",10},{"cy",15}}, 10)` | returns 2, leaves `{{"cy",15}}` |

## Notes

- One test removes from a vector of 400,000 elements: erasing them one at a time from the middle is O(n^2).
