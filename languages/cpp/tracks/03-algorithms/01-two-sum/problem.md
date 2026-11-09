# Treasure Pairs (Two Sum)

A pirate map lists the weights of buried chests. Exactly two chests together
weigh as much as the ship can carry. Find them.

Given an array `nums` and an integer `target`, return the indices `{i, j}`
with `i < j` such that `nums[i] + nums[j] == target`.

## Signature

```cpp
std::pair<int, int> two_sum(const std::vector<int>& nums, int target);
```

## Examples

| nums               | target | result   |
|--------------------|--------|----------|
| `{2, 7, 11, 15}`   | 9      | `{0, 1}` |
| `{3, 2, 4}`        | 6      | `{1, 2}` |
| `{3, 3}`           | 6      | `{0, 1}` |

## Notes

- Exactly one valid pair exists. The same element cannot be used twice.
- Values can be negative.
- Target: O(n) time. One of the tests has 1,000,000 elements and will time out an O(n^2) approach.
