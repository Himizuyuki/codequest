#include "mini_test.hpp"

#ifndef SOLUTION
#define SOLUTION "solution.cpp"
#endif
#include SOLUTION

// Each `constexpr` variable below forces the compiler to run the function.

TEST(fib_small) {
    constexpr long long f0 = fib(0);
    constexpr long long f1 = fib(1);
    constexpr long long f2 = fib(2);
    constexpr long long f10 = fib(10);
    CHECK_EQ(f0, 0LL);
    CHECK_EQ(f1, 1LL);
    CHECK_EQ(f2, 1LL);
    CHECK_EQ(f10, 55LL);
}

TEST(fib_large_needs_the_iterative_version) {
    constexpr long long f50 = fib(50);
    constexpr long long f90 = fib(90);
    CHECK_EQ(f50, 12586269025LL);
    CHECK_EQ(f90, 2880067194370816120LL);
}

TEST(primes_at_compile_time) {
    constexpr bool p2 = is_prime(2);
    constexpr bool p97 = is_prime(97);
    constexpr bool p91 = is_prime(91);      // 7 * 13
    constexpr bool p1 = is_prime(1);
    constexpr bool p0 = is_prime(0);
    constexpr bool pneg = is_prime(-7);
    CHECK_EQ(p2, true);
    CHECK_EQ(p97, true);
    CHECK_EQ(p91, false);
    CHECK_EQ(p1, false);
    CHECK_EQ(p0, false);
    CHECK_EQ(pneg, false);
}

TEST(primes_at_run_time_too) {
    volatile int big = 2147483647;          // a prime; volatile keeps this a run-time call
    CHECK_EQ(is_prime(big), true);
    volatile int square = 46337 * 46337;    // largest prime square below INT_MAX
    CHECK_EQ(is_prime(square), false);
}

TEST(first_primes_table) {
    constexpr auto five = first_primes<5>();
    CHECK_EQ(five, (std::array<int, 5>{2, 3, 5, 7, 11}));
    constexpr auto hundred = first_primes<100>();
    CHECK_EQ(hundred[9], 29);
    CHECK_EQ(hundred[99], 541);
    constexpr auto none = first_primes<0>();
    CHECK_EQ(none.size(), std::size_t{0});
}

TEST(counting_primes) {
    constexpr int below2 = count_primes_below(2);
    constexpr int below3 = count_primes_below(3);
    constexpr int below100 = count_primes_below(100);
    constexpr int below1000 = count_primes_below(1000);
    CHECK_EQ(below2, 0);
    CHECK_EQ(below3, 1);
    CHECK_EQ(below100, 25);
    CHECK_EQ(below1000, 168);
}

TEST(results_can_size_an_array) {
    std::array<char, static_cast<std::size_t>(fib(7)) + 1> buffer{};
    CHECK_EQ(buffer.size(), std::size_t{14});
}
