#include <climits>

#include "mini_test.hpp"

#ifndef SOLUTION
#define SOLUTION "solution.cpp"
#endif
#include SOLUTION

using S = std::string;

TEST(simple_shift) {
    CHECK_EQ(caesar("abc", 1), S("bcd"));
}

TEST(wraps_around) {
    CHECK_EQ(caesar("xyz", 3), S("abc"));
}

TEST(keeps_case_and_punctuation) {
    CHECK_EQ(caesar("Hello, World!", 13), S("Uryyb, Jbeyq!"));
}

TEST(negative_shift) {
    CHECK_EQ(caesar("abc", -1), S("zab"));
}

TEST(shift_larger_than_alphabet) {
    CHECK_EQ(caesar("abc", 53), S("bcd"));
    CHECK_EQ(caesar("a", -27), S("z"));
}

TEST(zero_and_empty) {
    CHECK_EQ(caesar("Unchanged 123", 0), S("Unchanged 123"));
    CHECK_EQ(caesar("", 5), S(""));
}

TEST(roundtrip) {
    S msg = "Meet me at Midnight, Agent K.";
    CHECK_EQ(caesar(caesar(msg, 7), -7), msg);
}

TEST(extreme_shift_does_not_overflow) {
    CHECK_EQ(caesar("a", INT_MIN), S("c"));
    CHECK_EQ(caesar("a", INT_MAX), S("x"));
}
