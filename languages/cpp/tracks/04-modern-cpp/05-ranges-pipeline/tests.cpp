#include "mini_test.hpp"

#ifndef SOLUTION
#define SOLUTION "solution.cpp"
#endif
#include SOLUTION

using V = std::vector<int>;
using W = std::vector<std::string>;

TEST(squares_of_evens_example) {
    CHECK_EQ(squares_of_evens(V{1, 2, 3, 4, 5, 6, 8}, 3), (V{4, 16, 36}));
}

TEST(squares_of_evens_fewer_than_limit) {
    CHECK_EQ(squares_of_evens(V{1, 2, 3}, 5), V{4});
    CHECK_EQ(squares_of_evens(V{1, 3, 5}, 2), V{});
    CHECK_EQ(squares_of_evens(V{}, 2), V{});
}

TEST(squares_of_evens_limit_zero_and_negatives) {
    CHECK_EQ(squares_of_evens(V{2, 4}, 0), V{});
    CHECK_EQ(squares_of_evens(V{-4, 0, 7, -2}, 3), (V{16, 0, 4}));
}

TEST(sum_while_positive_examples) {
    CHECK_EQ(sum_while_positive(V{3, 4, -1, 100}), 7LL);
    CHECK_EQ(sum_while_positive(V{0, 5}), 0LL);
    CHECK_EQ(sum_while_positive(V{}), 0LL);
    CHECK_EQ(sum_while_positive(V{1, 2, 3}), 6LL);
}

TEST(sum_while_positive_does_not_overflow) {
    CHECK_EQ(sum_while_positive(V{2000000000, 2000000000, 2000000000, 0}), 6000000000LL);
}

TEST(multiples) {
    CHECK_EQ(first_n_multiples(7, 4), (V{7, 14, 21, 28}));
    CHECK_EQ(first_n_multiples(1, 1), V{1});
    CHECK_EQ(first_n_multiples(5, 0), V{});
    CHECK_EQ(first_n_multiples(-3, 3), (V{-3, -6, -9}));
}

TEST(sort_by_length_example) {
    CHECK_EQ(sort_by_length({"pear", "fig", "apple", "kiwi"}), (W{"fig", "kiwi", "pear", "apple"}));
}

TEST(sort_by_length_ties_are_alphabetical) {
    CHECK_EQ(sort_by_length({"bb", "c", "aa", "a", "b", "ab"}), (W{"a", "b", "c", "aa", "ab", "bb"}));
    CHECK_EQ(sort_by_length({}), W{});
}

TEST(long_words) {
    CHECK_EQ(has_long_word(W{"a", "abc"}, 3), true);
    CHECK_EQ(has_long_word(W{"a", "abc"}, 4), false);
    CHECK_EQ(has_long_word(W{}, 0), false);
    CHECK_EQ(has_long_word(W{""}, 0), true);
}
