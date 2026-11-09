#include <numeric>

#include "mini_test.hpp"

#ifndef SOLUTION
#define SOLUTION "solution.cpp"
#endif
#include SOLUTION

using P = std::pair<int, int>;

TEST(basic) {
    CHECK_EQ(two_sum({2, 7, 11, 15}, 9), (P{0, 1}));
}

TEST(pair_not_at_the_start) {
    CHECK_EQ(two_sum({3, 2, 4}, 6), (P{1, 2}));
}

TEST(duplicates) {
    CHECK_EQ(two_sum({3, 3}, 6), (P{0, 1}));
}

TEST(negative_numbers) {
    CHECK_EQ(two_sum({-1, -2, -3, -4, -5}, -8), (P{2, 4}));
}

TEST(mixed_signs_and_zero) {
    CHECK_EQ(two_sum({0, 4, 3, 0}, 0), (P{0, 3}));
}

TEST(unordered_input) {
    CHECK_EQ(two_sum({10, -3, 8, 1, 15}, 23), (P{2, 4}));
}

TEST(large_input_needs_linear_time) {
    std::vector<int> nums(1000000);
    for (int i = 0; i < 1000000; ++i) nums[i] = i * 2;
    // Only the last two elements add up to this.
    CHECK_EQ(two_sum(nums, 2 * 999998 + 2 * 999999), (P{999998, 999999}));
}
