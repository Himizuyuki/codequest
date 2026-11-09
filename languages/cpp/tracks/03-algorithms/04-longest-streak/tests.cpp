#include <string>

#include "mini_test.hpp"

#ifndef SOLUTION
#define SOLUTION "solution.cpp"
#endif
#include SOLUTION

TEST(examples_from_the_statement) {
    CHECK_EQ(longest_unique_substring("abcabcbb"), 3);
    CHECK_EQ(longest_unique_substring("bbbbb"), 1);
    CHECK_EQ(longest_unique_substring("pwwkew"), 3);
}

TEST(empty_and_single) {
    CHECK_EQ(longest_unique_substring(""), 0);
    CHECK_EQ(longest_unique_substring("x"), 1);
}

TEST(all_distinct) {
    CHECK_EQ(longest_unique_substring("abcdef"), 6);
}

TEST(window_must_not_move_backwards) {
    CHECK_EQ(longest_unique_substring("abba"), 2);
    CHECK_EQ(longest_unique_substring("tmmzuxt"), 5);
}

TEST(repeat_in_the_middle) {
    CHECK_EQ(longest_unique_substring("dvdf"), 3);
    CHECK_EQ(longest_unique_substring("abcdbefg"), 6);   // "cdbefg"
}

TEST(case_and_symbols_are_distinct) {
    CHECK_EQ(longest_unique_substring("aAbB"), 4);
    CHECK_EQ(longest_unique_substring("a a a"), 2);   // "a " or " a"
}

TEST(all_256_byte_values) {
    std::string s;
    for (int i = 0; i < 256 * 100; ++i) s += static_cast<char>(i % 256);
    CHECK_EQ(longest_unique_substring(s), 256);
}

TEST(long_repeating_pattern) {
    std::string s;
    for (int i = 0; i < 200000; ++i) s += static_cast<char>('a' + i % 26);
    CHECK_EQ(longest_unique_substring(s), 26);
}
