#include <optional>

#include "mini_test.hpp"

#ifndef SOLUTION
#define SOLUTION "solution.cpp"
#endif
#include SOLUTION

using O = std::optional<int>;
static const O none = std::nullopt;

TEST(miss_on_empty_cache) {
    LRUCache c(2);
    CHECK_EQ(c.get(1), none);
    CHECK_EQ(c.size(), std::size_t{0});
}

TEST(put_then_get) {
    LRUCache c(2);
    c.put(1, 10);
    CHECK_EQ(c.get(1), O{10});
    CHECK_EQ(c.size(), std::size_t{1});
}

TEST(statement_example) {
    LRUCache c(2);
    c.put(1, 10);
    c.put(2, 20);
    CHECK_EQ(c.get(1), O{10});
    c.put(3, 30);                 // evicts 2
    CHECK_EQ(c.get(2), none);
    c.put(4, 40);                 // evicts 1
    CHECK_EQ(c.get(1), none);
    CHECK_EQ(c.get(3), O{30});
    CHECK_EQ(c.get(4), O{40});
    CHECK_EQ(c.size(), std::size_t{2});
}

TEST(updating_a_key_keeps_the_size_and_refreshes_it) {
    LRUCache c(2);
    c.put(1, 10);
    c.put(2, 20);
    c.put(1, 11);                 // update: 1 is now the most recent
    CHECK_EQ(c.size(), std::size_t{2});
    c.put(3, 30);                 // evicts 2, not 1
    CHECK_EQ(c.get(1), O{11});
    CHECK_EQ(c.get(2), none);
    CHECK_EQ(c.get(3), O{30});
}

TEST(a_missed_get_does_not_change_the_order) {
    LRUCache c(2);
    c.put(1, 10);
    c.put(2, 20);
    CHECK_EQ(c.get(99), none);
    c.put(3, 30);                 // still evicts 1
    CHECK_EQ(c.get(1), none);
    CHECK_EQ(c.get(2), O{20});
}

TEST(capacity_one) {
    LRUCache c(1);
    c.put(1, 10);
    c.put(2, 20);
    CHECK_EQ(c.get(1), none);
    CHECK_EQ(c.get(2), O{20});
    c.put(2, 21);
    CHECK_EQ(c.get(2), O{21});
    CHECK_EQ(c.size(), std::size_t{1});
}

TEST(negative_keys_and_zero_values) {
    LRUCache c(3);
    c.put(-1, 0);
    c.put(0, -5);
    CHECK_EQ(c.get(-1), O{0});
    CHECK_EQ(c.get(0), O{-5});
}

TEST(a_million_operations) {
    const int capacity = 50000;
    LRUCache c(capacity);
    for (int i = 0; i < 500000; ++i) c.put(i, i * 2);
    CHECK_EQ(c.size(), static_cast<std::size_t>(capacity));
    CHECK_EQ(c.get(0), none);
    CHECK_EQ(c.get(449999), none);
    long long sum = 0;
    for (int i = 450000; i < 500000; ++i) sum += c.get(i).value_or(-1);
    CHECK_EQ(sum, 2LL * (450000LL + 499999LL) * 50000LL / 2LL);
    // Touch the oldest survivor, then add one more: the second oldest must be the one evicted.
    CHECK_EQ(c.get(450000), O{900000});
    c.put(1000000, 1);
    CHECK_EQ(c.get(450000), O{900000});
    CHECK_EQ(c.get(450001), none);
    for (int i = 0; i < 450000; ++i) c.get(i);   // misses must stay cheap
    CHECK_EQ(c.size(), static_cast<std::size_t>(capacity));
}
