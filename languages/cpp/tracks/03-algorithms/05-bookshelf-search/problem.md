# Bookshelf Search (Binary Search)

The library's shelves are sorted, and the librarian refuses to walk past every book.

```cpp
int lower_bound_index(const std::vector<int>& sorted, int x);
int count_equal(const std::vector<int>& sorted, int x);
long long isqrt(long long n);
```

- **`lower_bound_index`**: index of the first element `>= x`, or `sorted.size()` if there is none.
- **`count_equal`**: how many elements equal `x`.
- **`isqrt`**: the largest integer `r` with `r * r <= n`, for `n >= 0`. No floating point.

`sorted` is in ascending order and may contain duplicates.

## Examples

| call | result |
|---|---|
| `lower_bound_index({1,3,3,5,8}, 3)` | 1 |
| `lower_bound_index({1,3,3,5,8}, 4)` | 3 |
| `lower_bound_index({1,3,3,5,8}, 9)` | 5 |
| `count_equal({1,3,3,5,8}, 3)` | 2 |
| `isqrt(15)`, `isqrt(16)` | 3, 4 |
| `isqrt(1000000000000000000)` | 1000000000 |

## Notes

- Target: O(log n) per call. One test makes 200,000 queries on a million elements.
- `isqrt` must be exact up to `LLONG_MAX`; `std::sqrt` on a `double` is not.
