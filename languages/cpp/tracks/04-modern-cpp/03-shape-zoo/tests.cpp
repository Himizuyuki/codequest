#include <cmath>

#include "mini_test.hpp"

#ifndef SOLUTION
#define SOLUTION "solution.cpp"
#endif
#include SOLUTION

static const double kPi = 3.14159265358979323846;

#define CHECK_NEAR(actual, expected)                                                        \
    do {                                                                                    \
        const double mt_a = (actual);                                                       \
        const double mt_e = (expected);                                                     \
        if (!(std::fabs(mt_a - mt_e) < 1e-9))                                               \
            throw mt::Failure{"line " + std::to_string(__LINE__) + ": " #actual             \
                              "\n        got:      " + std::to_string(mt_a) +               \
                              "\n        expected: " + std::to_string(mt_e)};               \
    } while (0)

TEST(circle_area) {
    CHECK_NEAR(area(Circle{1.0}), kPi);
    CHECK_NEAR(area(Circle{2.0}), 4.0 * kPi);
    CHECK_NEAR(area(Circle{0.0}), 0.0);
}

TEST(rectangle_area) {
    CHECK_NEAR(area(Rect{3.0, 4.0}), 12.0);
    CHECK_NEAR(area(Rect{0.5, 0.5}), 0.25);
}

TEST(triangle_area) {
    CHECK_NEAR(area(Triangle{3.0, 4.0, 5.0}), 6.0);
    CHECK_NEAR(area(Triangle{2.0, 2.0, 2.0}), std::sqrt(3.0));
}

TEST(names) {
    CHECK_EQ(name(Circle{1.0}), std::string("circle"));
    CHECK_EQ(name(Rect{1.0, 2.0}), std::string("rectangle"));
    CHECK_EQ(name(Triangle{3.0, 4.0, 5.0}), std::string("triangle"));
}

TEST(a_shape_can_change_kind) {
    Shape s = Circle{1.0};
    CHECK_EQ(name(s), std::string("circle"));
    s = Rect{2.0, 5.0};
    CHECK_EQ(name(s), std::string("rectangle"));
    CHECK_NEAR(area(s), 10.0);
}

TEST(total_area_of_the_zoo) {
    std::vector<Shape> zoo{Circle{1.0}, Rect{3.0, 4.0}, Triangle{3.0, 4.0, 5.0}};
    CHECK_NEAR(total_area(zoo), kPi + 12.0 + 6.0);
    CHECK_NEAR(total_area({}), 0.0);
}

TEST(counting_circles) {
    std::vector<Shape> zoo{Circle{1.0}, Rect{3.0, 4.0}, Circle{2.0}, Triangle{3.0, 4.0, 5.0}, Circle{3.0}};
    CHECK_EQ(count_circles(zoo), 3);
    CHECK_EQ(count_circles({}), 0);
    CHECK_EQ(count_circles({Rect{1.0, 1.0}}), 0);
}
