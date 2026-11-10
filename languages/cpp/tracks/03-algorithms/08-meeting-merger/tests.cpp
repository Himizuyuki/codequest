#include <algorithm>
#include <random>

#include "mini_test.hpp"

#ifndef SOLUTION
#define SOLUTION "solution.cpp"
#endif
#include SOLUTION

using I = std::vector<std::pair<int, int>>;

TEST(classic_example) {
    CHECK_EQ(merge_intervals({{1, 3}, {2, 6}, {8, 10}, {15, 18}}), (I{{1, 6}, {8, 10}, {15, 18}}));
}

TEST(touching_intervals_merge) {
    CHECK_EQ(merge_intervals({{1, 4}, {4, 5}}), (I{{1, 5}}));
}

TEST(unsorted_input) {
    CHECK_EQ(merge_intervals({{5, 7}, {1, 2}, {2, 3}}), (I{{1, 3}, {5, 7}}));
}

TEST(one_interval_contains_the_others) {
    CHECK_EQ(merge_intervals({{1, 10}, {2, 3}, {4, 5}}), (I{{1, 10}}));
}

TEST(nothing_overlaps) {
    CHECK_EQ(merge_intervals({{7, 8}, {1, 2}, {4, 5}}), (I{{1, 2}, {4, 5}, {7, 8}}));
}

TEST(single_point_and_negative) {
    CHECK_EQ(merge_intervals({{3, 3}}), (I{{3, 3}}));
    CHECK_EQ(merge_intervals({{-5, -1}, {-2, 4}, {6, 6}}), (I{{-5, 4}, {6, 6}}));
}

TEST(empty_input) {
    CHECK_EQ(merge_intervals({}), I{});
}

TEST(two_hundred_thousand_intervals) {
    I in;
    for (int i = 0; i < 200000; ++i) in.push_back({i, i + 1});
    std::mt19937 rng(3);
    std::shuffle(in.begin(), in.end(), rng);
    CHECK_EQ(merge_intervals(in), (I{{0, 200000}}));
}
