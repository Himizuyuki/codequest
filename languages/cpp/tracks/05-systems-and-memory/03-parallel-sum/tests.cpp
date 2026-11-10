#include <thread>

#include "mini_test.hpp"

#ifndef SOLUTION
#define SOLUTION "solution.cpp"
#endif
#include SOLUTION

using V = std::vector<int>;

TEST(sum_small) {
    CHECK_EQ(parallel_sum(V{1, 2, 3, 4, 5}, 2), 15LL);
    CHECK_EQ(parallel_sum(V{1, 2, 3, 4, 5}, 1), 15LL);
    CHECK_EQ(parallel_sum(V{-5, 5, -7}, 3), -7LL);
}

TEST(sum_empty) {
    CHECK_EQ(parallel_sum(V{}, 1), 0LL);
    CHECK_EQ(parallel_sum(V{}, 4), 0LL);
}

TEST(more_threads_than_elements) {
    CHECK_EQ(parallel_sum(V{10, 20, 30}, 8), 60LL);
    CHECK_EQ(parallel_sum(V{42}, 16), 42LL);
}

TEST(every_thread_count_gives_the_same_answer) {
    V v(1000);
    for (int i = 0; i < 1000; ++i) v[i] = i * 3 - 500;
    long long expected = 0;
    for (int x : v) expected += x;
    for (unsigned t = 1; t <= 13; ++t) CHECK_EQ(parallel_sum(v, t), expected);
}

TEST(large_input_without_overflow) {
    V v(3000000, 2000000000);
    CHECK_EQ(parallel_sum(v, 4), 6000000000000000LL);
    CHECK_EQ(parallel_sum(v, 7), 6000000000000000LL);
}

TEST(counter_single_thread) {
    SafeCounter c;
    CHECK_EQ(c.value(), 0LL);
    for (int i = 0; i < 1000; ++i) c.increment();
    CHECK_EQ(c.value(), 1000LL);
}

TEST(counter_hammered_by_eight_threads) {
    for (int round = 0; round < 5; ++round) {
        SafeCounter c;
        {
            std::vector<std::jthread> workers;
            for (int t = 0; t < 8; ++t)
                workers.emplace_back([&c] {
                    for (int i = 0; i < 200000; ++i) c.increment();
                });
        }   // all workers joined here
        CHECK_EQ(c.value(), 1600000LL);
    }
}
