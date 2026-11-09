#include "mini_test.hpp"

#ifndef SOLUTION
#define SOLUTION "solution.cpp"
#endif
#include SOLUTION

using S = std::string;

TEST(to_roman_small) {
    CHECK_EQ(to_roman(1), S("I"));
    CHECK_EQ(to_roman(3), S("III"));
    CHECK_EQ(to_roman(8), S("VIII"));
}

TEST(to_roman_subtractive) {
    CHECK_EQ(to_roman(4), S("IV"));
    CHECK_EQ(to_roman(9), S("IX"));
    CHECK_EQ(to_roman(40), S("XL"));
    CHECK_EQ(to_roman(90), S("XC"));
    CHECK_EQ(to_roman(400), S("CD"));
    CHECK_EQ(to_roman(900), S("CM"));
}

TEST(to_roman_big) {
    CHECK_EQ(to_roman(58), S("LVIII"));
    CHECK_EQ(to_roman(1994), S("MCMXCIV"));
    CHECK_EQ(to_roman(3999), S("MMMCMXCIX"));
}

TEST(from_roman_examples) {
    CHECK_EQ(from_roman("I"), 1);
    CHECK_EQ(from_roman("IV"), 4);
    CHECK_EQ(from_roman("LVIII"), 58);
    CHECK_EQ(from_roman("MCMXCIV"), 1994);
    CHECK_EQ(from_roman("MMMCMXCIX"), 3999);
}

TEST(roundtrip_whole_range) {
    for (int n = 1; n <= 3999; ++n) {
        S numeral = to_roman(n);
        CHECK(!numeral.empty());
        CHECK_EQ(from_roman(numeral), n);
    }
}
