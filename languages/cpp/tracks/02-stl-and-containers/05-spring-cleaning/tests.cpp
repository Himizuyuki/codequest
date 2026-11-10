#include "mini_test.hpp"

#ifndef SOLUTION
#define SOLUTION "solution.cpp"
#endif
#include SOLUTION

using V = std::vector<int>;
using M = std::map<std::string, int>;

TEST(remove_evens) {
    V v{1, 2, 3, 4, 5, 6};
    remove_multiples(v, 2);
    CHECK_EQ(v, (V{1, 3, 5}));
}

TEST(remove_keeps_order_and_handles_neighbours) {
    V v{6, 6, 6, 1, 9, 9, 2, 3, 3};
    remove_multiples(v, 3);
    CHECK_EQ(v, (V{1, 2}));
}

TEST(remove_zero_and_negatives) {
    V v{0, -4, 5, -5, 7};
    remove_multiples(v, 5);
    CHECK_EQ(v, (V{-4, 7}));
}

TEST(remove_everything_or_nothing) {
    V all{2, 4, 6};
    remove_multiples(all, 1);
    CHECK_EQ(all, V{});
    V none{1, 3, 5};
    remove_multiples(none, 2);
    CHECK_EQ(none, (V{1, 3, 5}));
}

TEST(remove_from_a_large_vector) {
    V v(400000);
    for (int i = 0; i < 400000; ++i) v[i] = i;
    remove_multiples(v, 1);
    CHECK_EQ(v.size(), std::size_t{0});
    V w(400000, 2);
    w.push_back(3);
    remove_multiples(w, 2);
    CHECK_EQ(w, V{3});
}

TEST(sorted_unique_basic) {
    CHECK_EQ(sorted_unique({3, 1, 3, 2, 1}), (V{1, 2, 3}));
    CHECK_EQ(sorted_unique({}), V{});
    CHECK_EQ(sorted_unique({7, 7, 7}), V{7});
    CHECK_EQ(sorted_unique({-1, 5, -1, 0}), (V{-1, 0, 5}));
}

TEST(evict_expired_sessions) {
    M s{{"ann", 5}, {"bob", 10}, {"cy", 15}};
    CHECK_EQ(evict_expired(s, 10), 2);
    CHECK_EQ(s, (M{{"cy", 15}}));
}

TEST(evict_nothing_and_everything) {
    M s{{"ann", 5}, {"bob", 10}};
    CHECK_EQ(evict_expired(s, 1), 0);
    CHECK_EQ(s.size(), std::size_t{2});
    CHECK_EQ(evict_expired(s, 100), 2);
    CHECK_EQ(s.size(), std::size_t{0});
    CHECK_EQ(evict_expired(s, 100), 0);
}
