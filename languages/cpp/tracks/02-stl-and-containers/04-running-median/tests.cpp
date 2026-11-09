#include <algorithm>
#include <numeric>
#include <random>

#include "mini_test.hpp"

#ifndef SOLUTION
#define SOLUTION "solution.cpp"
#endif
#include SOLUTION

TEST(empty_throws) {
    RunningMedian m;
    CHECK_THROWS(m.median());
}

TEST(single_number) {
    RunningMedian m;
    m.add(7);
    CHECK_EQ(m.median(), 7.0);
}

TEST(two_numbers_average) {
    RunningMedian m;
    m.add(1);
    m.add(2);
    CHECK_EQ(m.median(), 1.5);
}

TEST(statement_example) {
    RunningMedian m;
    m.add(5);
    CHECK_EQ(m.median(), 5.0);
    m.add(15);
    CHECK_EQ(m.median(), 10.0);
    m.add(1);
    CHECK_EQ(m.median(), 5.0);
    m.add(3);
    CHECK_EQ(m.median(), 4.0);
}

TEST(descending_and_negative) {
    RunningMedian m;
    for (int x : {10, 5, 0, -5, -10}) m.add(x);
    CHECK_EQ(m.median(), 0.0);
    m.add(-20);
    CHECK_EQ(m.median(), -2.5);
}

TEST(duplicates) {
    RunningMedian m;
    for (int i = 0; i < 5; ++i) m.add(4);
    CHECK_EQ(m.median(), 4.0);
    m.add(100);
    CHECK_EQ(m.median(), 4.0);
}

TEST(no_int_overflow_in_average) {
    RunningMedian m;
    m.add(2000000000);
    m.add(2000000000);
    CHECK_EQ(m.median(), 2000000000.0);
}

TEST(matches_a_sorted_copy) {
    std::mt19937 rng(7);
    RunningMedian m;
    std::vector<int> seen;
    for (int i = 0; i < 300; ++i) {
        int x = static_cast<int>(rng() % 201) - 100;
        m.add(x);
        seen.push_back(x);
        std::vector<int> sorted = seen;
        std::sort(sorted.begin(), sorted.end());
        double expected = sorted.size() % 2 ? sorted[sorted.size() / 2]
                                            : (sorted[sorted.size() / 2 - 1] + sorted[sorted.size() / 2]) / 2.0;
        CHECK_EQ(m.median(), expected);
    }
}

TEST(two_hundred_thousand_numbers) {
    std::vector<int> nums(200000);
    std::iota(nums.begin(), nums.end(), 0);
    std::mt19937 rng(99);
    std::shuffle(nums.begin(), nums.end(), rng);
    RunningMedian m;
    for (int x : nums) m.add(x);
    CHECK_EQ(m.median(), 99999.5);   // numbers 0..199999
}
