#include <string>

#include "mini_test.hpp"

#ifndef SOLUTION
#define SOLUTION "solution.cpp"
#endif
#include SOLUTION

TEST(empty_is_balanced) {
    CHECK_EQ(is_balanced(""), true);
}

TEST(all_three_kinds) {
    CHECK_EQ(is_balanced("()[]{}"), true);
}

TEST(nested) {
    CHECK_EQ(is_balanced("{[()]}"), true);
    CHECK_EQ(is_balanced("((([[[{{{}}}]]])))"), true);
}

TEST(wrong_type) {
    CHECK_EQ(is_balanced("(]"), false);
}

TEST(wrong_order) {
    CHECK_EQ(is_balanced("([)]"), false);
}

TEST(unclosed) {
    CHECK_EQ(is_balanced("(("), false);
    CHECK_EQ(is_balanced("{[]"), false);
}

TEST(closing_without_opening) {
    CHECK_EQ(is_balanced("))"), false);
    CHECK_EQ(is_balanced("]"), false);
    CHECK_EQ(is_balanced("())("), false);
}

TEST(other_characters_are_ignored) {
    CHECK_EQ(is_balanced("a(b)c[d]{e}"), true);
    CHECK_EQ(is_balanced("if (x > 0) { return x[0]; }"), true);
    CHECK_EQ(is_balanced("no brackets at all"), true);
}

TEST(two_million_characters) {
    std::string big(1000000, '(');
    big += std::string(1000000, ')');
    CHECK_EQ(is_balanced(big), true);
    big.back() = ']';
    CHECK_EQ(is_balanced(big), false);
}
