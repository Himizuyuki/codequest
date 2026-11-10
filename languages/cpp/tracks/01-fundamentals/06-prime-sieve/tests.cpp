#include "mini_test.hpp"

#ifndef SOLUTION
#define SOLUTION "solution.cpp"
#endif
#include SOLUTION

using V = std::vector<int>;

TEST(up_to_ten) {
    CHECK_EQ(primes_up_to(10), (V{2, 3, 5, 7}));
}

TEST(two_is_included) {
    CHECK_EQ(primes_up_to(2), V{2});
    CHECK_EQ(primes_up_to(3), (V{2, 3}));
}

TEST(below_two_is_empty) {
    CHECK_EQ(primes_up_to(1), V{});
    CHECK_EQ(primes_up_to(0), V{});
    CHECK_EQ(primes_up_to(-5), V{});
}

TEST(up_to_one_hundred) {
    V p = primes_up_to(100);
    CHECK_EQ(p.size(), std::size_t{25});
    CHECK_EQ(p.back(), 97);
}

TEST(squares_of_primes_are_not_prime) {
    V p = primes_up_to(50);
    CHECK_EQ(p, (V{2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47}));
}

TEST(ten_million) {
    V p = primes_up_to(10000000);
    CHECK_EQ(p.size(), std::size_t{664579});
    CHECK_EQ(p.back(), 9999991);
}
