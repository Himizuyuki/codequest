#include "mini_test.hpp"

#ifndef SOLUTION
#define SOLUTION "solution.cpp"
#endif
#include SOLUTION

using V = std::vector<int>;

TEST(classic_example) {
    CHECK_EQ(max_water(V{1, 8, 6, 2, 5, 4, 8, 3, 7}), 49LL);
}

TEST(two_equal_walls_at_the_ends) {
    CHECK_EQ(max_water(V{4, 3, 2, 1, 4}), 16LL);
    CHECK_EQ(max_water(V{1, 2, 1}), 2LL);
    CHECK_EQ(max_water(V{1, 1}), 1LL);
}

TEST(fewer_than_two_walls) {
    CHECK_EQ(max_water(V{}), 0LL);
    CHECK_EQ(max_water(V{5}), 0LL);
}

TEST(zero_height_walls) {
    CHECK_EQ(max_water(V{0, 0}), 0LL);
    CHECK_EQ(max_water(V{0, 5, 0}), 0LL);
}

TEST(best_pair_is_in_the_middle) {
    CHECK_EQ(max_water(V{2, 3, 4, 5, 18, 17, 6}), 17LL);
}

TEST(increasing_and_decreasing) {
    CHECK_EQ(max_water(V{1, 2, 3, 4, 5}), 6LL);   // 2 and 5 (2 * 3) or 3 and 5 (3 * 2)
    CHECK_EQ(max_water(V{5, 4, 3, 2, 1}), 6LL);
}

TEST(large_input_needs_linear_time) {
    V h(1000000, 10000);
    CHECK_EQ(max_water(h), 10000LL * 999999LL);   // about 10^10: does not fit in a 32-bit int
}
