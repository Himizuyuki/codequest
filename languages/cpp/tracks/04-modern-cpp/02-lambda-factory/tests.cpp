#include "mini_test.hpp"

#ifndef SOLUTION
#define SOLUTION "solution.cpp"
#endif
#include SOLUTION

TEST(counter_counts_from_start) {
    auto next = make_counter(5);
    CHECK_EQ(next(), 5);
    CHECK_EQ(next(), 6);
    CHECK_EQ(next(), 7);
}

TEST(counters_are_independent) {
    auto a = make_counter(0);
    auto b = make_counter(100);
    CHECK_EQ(a(), 0);
    CHECK_EQ(b(), 100);
    CHECK_EQ(a(), 1);
    CHECK_EQ(b(), 101);
}

TEST(copying_a_counter_copies_its_state) {
    auto a = make_counter(10);
    CHECK_EQ(a(), 10);
    auto b = a;            // std::function copy: b has its own n == 11
    CHECK_EQ(a(), 11);
    CHECK_EQ(a(), 12);
    CHECK_EQ(b(), 11);
}

TEST(multiplier) {
    auto triple = make_multiplier(3);
    CHECK_EQ(triple(7), 21);
    CHECK_EQ(triple(-2), -6);
    CHECK_EQ(make_multiplier(0)(99), 0);
}

TEST(adders_each_remember_their_own_index) {
    auto adders = make_adders(5);
    CHECK_EQ(adders.size(), std::size_t{5});
    for (int i = 0; i < 5; ++i) CHECK_EQ(adders[i](10), 10 + i);
}

TEST(no_adders) {
    CHECK_EQ(make_adders(0).size(), std::size_t{0});
}

TEST(compose_applies_g_then_f) {
    auto add3 = [](int x) { return x + 3; };
    auto twice = [](int x) { return x * 2; };
    CHECK_EQ(compose(twice, add3)(1), 8);    // (1 + 3) * 2
    CHECK_EQ(compose(add3, twice)(1), 5);    // 1 * 2 + 3
}

TEST(compose_outlives_its_arguments) {
    std::function<int(int)> h;
    {
        auto adders = make_adders(4);
        CHECK_EQ(adders.size(), std::size_t{4});
        h = compose(make_multiplier(2), adders[3]);
    }
    CHECK_EQ(h(1), 8);
}

TEST(apply_n_times) {
    CHECK_EQ(apply_n(make_multiplier(2), 10, 1), 1024);
    CHECK_EQ(apply_n([](int x) { return x - 1; }, 3, 0), -3);
    CHECK_EQ(apply_n(make_multiplier(5), 0, 7), 7);
}
