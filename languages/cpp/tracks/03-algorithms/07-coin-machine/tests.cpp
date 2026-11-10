#include "mini_test.hpp"

#ifndef SOLUTION
#define SOLUTION "solution.cpp"
#endif
#include SOLUTION

using V = std::vector<int>;

TEST(classic_example) {
    CHECK_EQ(min_coins(V{1, 2, 5}, 11), 3);
}

TEST(impossible) {
    CHECK_EQ(min_coins(V{2}, 3), -1);
    CHECK_EQ(min_coins(V{5, 10}, 3), -1);
}

TEST(zero_amount_needs_no_coin) {
    CHECK_EQ(min_coins(V{1, 2, 5}, 0), 0);
    CHECK_EQ(min_coins(V{7}, 0), 0);
}

TEST(greedy_is_wrong_here) {
    CHECK_EQ(min_coins(V{1, 3, 4}, 6), 2);
    CHECK_EQ(min_coins(V{1, 5, 6, 9}, 11), 2);   // 5 + 6, not 9 + 1 + 1
}

TEST(single_coin) {
    CHECK_EQ(min_coins(V{7}, 49), 7);
    CHECK_EQ(min_coins(V{7}, 50), -1);
}

TEST(awkward_coins) {
    CHECK_EQ(min_coins(V{186, 419, 83, 408}, 6249), 20);
}

TEST(large_amount) {
    CHECK_EQ(min_coins(V{1, 5, 10, 25}, 100000), 4000);
    CHECK_EQ(min_coins(V{2, 4, 6, 8, 10, 12, 14, 16, 18, 20}, 99999), -1);
}
