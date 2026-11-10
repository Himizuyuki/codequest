#include <climits>

#include "mini_test.hpp"

#ifndef SOLUTION
#define SOLUTION "solution.cpp"
#endif
#include SOLUTION

using V = std::vector<int>;

TEST(lower_bound_examples) {
    V v{1, 3, 3, 5, 8};
    CHECK_EQ(lower_bound_index(v, 3), 1);
    CHECK_EQ(lower_bound_index(v, 4), 3);
    CHECK_EQ(lower_bound_index(v, 9), 5);
    CHECK_EQ(lower_bound_index(v, 0), 0);
    CHECK_EQ(lower_bound_index(v, 8), 4);
}

TEST(lower_bound_empty_and_single) {
    CHECK_EQ(lower_bound_index(V{}, 7), 0);
    CHECK_EQ(lower_bound_index(V{7}, 7), 0);
    CHECK_EQ(lower_bound_index(V{7}, 8), 1);
}

TEST(count_equal_examples) {
    V v{1, 3, 3, 5, 8};
    CHECK_EQ(count_equal(v, 3), 2);
    CHECK_EQ(count_equal(v, 4), 0);
    CHECK_EQ(count_equal(v, 8), 1);
    CHECK_EQ(count_equal(V{}, 1), 0);
    CHECK_EQ(count_equal(V{2, 2, 2, 2}, 2), 4);
}

TEST(many_queries_need_log_time) {
    V v(1000000);
    for (int i = 0; i < 1000000; ++i) v[i] = (i / 4) * 2;   // each even number 4 times
    long long checksum = 0;
    for (int q = 0; q < 200000; ++q) {
        int x = (q * 37) % 500000;
        checksum += lower_bound_index(v, x) + count_equal(v, x);
    }
    // even x: index 2x, count 4; odd x: index 2(x+1), count 0
    long long expected = 0;
    for (int q = 0; q < 200000; ++q) {
        int x = (q * 37) % 500000;
        expected += (x % 2 == 0) ? 2LL * x + 4 : 2LL * (x + 1);
    }
    CHECK_EQ(checksum, expected);
}

TEST(isqrt_small) {
    CHECK_EQ(isqrt(0), 0LL);
    CHECK_EQ(isqrt(1), 1LL);
    CHECK_EQ(isqrt(3), 1LL);
    CHECK_EQ(isqrt(4), 2LL);
    CHECK_EQ(isqrt(15), 3LL);
    CHECK_EQ(isqrt(16), 4LL);
}

TEST(isqrt_huge) {
    CHECK_EQ(isqrt(1000000000000000000LL), 1000000000LL);
    CHECK_EQ(isqrt(999999999999999999LL), 999999999LL);
    CHECK_EQ(isqrt(LLONG_MAX), 3037000499LL);
    CHECK_EQ(isqrt(3037000499LL * 3037000499LL - 1), 3037000498LL);
}
