# Shape Zoo (variant & visit)

The zoo keeps three kinds of shapes in the same enclosure. No base class, no `virtual`: a shape is a
`std::variant`, a type-safe "one of these".

```cpp
struct Circle   { double r; };
struct Rect     { double w, h; };
struct Triangle { double a, b, c; };          // the three side lengths
using Shape = std::variant<Circle, Rect, Triangle>;

double area(const Shape& shape);
std::string name(const Shape& shape);          // "circle", "rectangle" or "triangle"
double total_area(const std::vector<Shape>& shapes);
int count_circles(const std::vector<Shape>& shapes);
```

The types are already in `solution.cpp` - do not change them.

## Formulas

- circle: pi * r^2 (use `std::numbers::pi` from `<numbers>`, C++20)
- rectangle: w * h
- triangle (Heron): with `p = (a + b + c) / 2`, area = `sqrt(p (p - a) (p - b) (p - c))`

## Examples

| shape | area | name |
|---|---|---|
| `Circle{2}` | 12.566... | `circle` |
| `Rect{3, 4}` | 12 | `rectangle` |
| `Triangle{3, 4, 5}` | 6 | `triangle` |

Results are checked with a tolerance of 1e-9.
