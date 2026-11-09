#include "mini_test.hpp"

#ifndef SOLUTION
#define SOLUTION "solution.cpp"
#endif
#include SOLUTION

using R = std::vector<std::pair<std::string, int>>;

TEST(empty_text) {
    CHECK_EQ(top_words("", 3), R{});
}

TEST(k_is_zero) {
    CHECK_EQ(top_words("a b c", 0), R{});
}

TEST(single_winner_then_alphabetical_ties) {
    R got = top_words("the quick brown fox jumps over the lazy dog the end", 2);
    CHECK_EQ(got, (R{{"the", 3}, {"brown", 1}}));
}

TEST(ties_break_alphabetically) {
    R got = top_words("To be, or not to be: that is the question.", 3);
    CHECK_EQ(got, (R{{"be", 2}, {"to", 2}, {"is", 1}}));
}

TEST(case_insensitive) {
    R got = top_words("Apple apple APPLE banana Banana", 5);
    CHECK_EQ(got, (R{{"apple", 3}, {"banana", 2}}));
}

TEST(non_letters_separate_words) {
    R got = top_words("it's 42 time", 5);
    CHECK_EQ(got, (R{{"it", 1}, {"s", 1}, {"time", 1}}));
}

TEST(k_larger_than_distinct_words) {
    CHECK_EQ(top_words("one two two", 10), (R{{"two", 2}, {"one", 1}}));
}

TEST(handles_large_input) {
    std::string big;
    for (int i = 0; i < 200000; ++i) big += (i % 3 == 0 ? "alpha " : i % 3 == 1 ? "beta " : "gamma ");
    R got = top_words(big, 2);
    CHECK_EQ(got.size(), std::size_t{2});
    CHECK_EQ(got[0].first, std::string("alpha"));
    CHECK_EQ(got[0].second, 66667);
}
