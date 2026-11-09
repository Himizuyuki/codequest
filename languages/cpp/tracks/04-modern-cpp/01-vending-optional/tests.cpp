#include <climits>
#include <optional>

#include "mini_test.hpp"

#ifndef SOLUTION
#define SOLUTION "solution.cpp"
#endif
#include SOLUTION

using O = std::optional<int>;
static const O none = std::nullopt;

TEST(parse_valid_numbers) {
    CHECK_EQ(parse_int("42"), O{42});
    CHECK_EQ(parse_int("0"), O{0});
    CHECK_EQ(parse_int("-7"), O{-7});
    CHECK_EQ(parse_int("007"), O{7});
}

TEST(parse_rejects_garbage) {
    CHECK_EQ(parse_int(""), none);
    CHECK_EQ(parse_int("-"), none);
    CHECK_EQ(parse_int("abc"), none);
    CHECK_EQ(parse_int("12a"), none);
    CHECK_EQ(parse_int("1 2"), none);
}

TEST(parse_rejects_spaces_and_plus) {
    CHECK_EQ(parse_int(" 5"), none);
    CHECK_EQ(parse_int("5 "), none);
    CHECK_EQ(parse_int("+5"), none);
}

TEST(parse_int_limits) {
    CHECK_EQ(parse_int("2147483647"), O{INT_MAX});
    CHECK_EQ(parse_int("-2147483648"), O{INT_MIN});
    CHECK_EQ(parse_int("2147483648"), none);
    CHECK_EQ(parse_int("-2147483649"), none);
    CHECK_EQ(parse_int("99999999999999999999"), none);
}

TEST(safe_div_basic) {
    CHECK_EQ(safe_div(7, 2), O{3});
    CHECK_EQ(safe_div(-7, 2), O{-3});
    CHECK_EQ(safe_div(0, 5), O{0});
}

TEST(safe_div_undefined_cases) {
    CHECK_EQ(safe_div(1, 0), none);
    CHECK_EQ(safe_div(INT_MIN, -1), none);
    CHECK_EQ(safe_div(INT_MIN, 1), O{INT_MIN});
}

TEST(divide_strings_happy_path) {
    CHECK_EQ(divide_strings("100", "8"), O{12});
    CHECK_EQ(divide_strings("-9", "3"), O{-3});
}

TEST(divide_strings_failures) {
    CHECK_EQ(divide_strings("100", "x"), none);
    CHECK_EQ(divide_strings("x", "5"), none);
    CHECK_EQ(divide_strings("5", "0"), none);
    CHECK_EQ(divide_strings("-2147483648", "-1"), none);
}
