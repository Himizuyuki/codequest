#include <cmath>
#include <numbers>
#include <string>
#include <variant>
#include <vector>

// Do not change these types - the tests build shapes with them.
struct Circle {
    double r;
};
struct Rect {
    double w, h;
};
struct Triangle {
    double a, b, c;
};
using Shape = std::variant<Circle, Rect, Triangle>;

double area(const Shape& shape) {
    // TODO: see problem.md
    return -1.0;
}

std::string name(const Shape& shape) {
    // TODO: see problem.md
    return "";
}

double total_area(const std::vector<Shape>& shapes) {
    // TODO: see problem.md
    return -1.0;
}

int count_circles(const std::vector<Shape>& shapes) {
    // TODO: see problem.md
    return -1;
}
