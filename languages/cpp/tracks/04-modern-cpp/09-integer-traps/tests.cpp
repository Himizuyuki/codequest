#include <climits>

#include "mini_test.hpp"

#ifndef SOLUTION
#define SOLUTION "solution.cpp"
#endif
#include SOLUTION

TEST(safe_less_negative_vs_unsigned) {
    CHECK_EQ(safe_less(-1, 1u), true);
    CHECK_EQ(safe_less(-1, 0u), true);
    CHECK_EQ(safe_less(INT_MIN, UINT_MAX), true);
    CHECK_EQ(safe_less(-1, UINT_MAX), true);
}

TEST(safe_less_ordinary_cases) {
    CHECK_EQ(safe_less(1, 2u), true);
    CHECK_EQ(safe_less(2, 1u), false);
    CHECK_EQ(safe_less(5, 5u), false);
    CHECK_EQ(safe_less(0, 0u), false);
    CHECK_EQ(safe_less(INT_MAX, UINT_MAX), true);
    CHECK_EQ(safe_less(INT_MAX, 7u), false);
}

TEST(midpoint_small) {
    CHECK_EQ(midpoint(2, 6), 4);
    CHECK_EQ(midpoint(1, 4), 2);     // 2.5 rounds towards a = 1
    CHECK_EQ(midpoint(4, 1), 3);     // 2.5 rounds towards a = 4
    CHECK_EQ(midpoint(-3, -8), -5);  // -5.5 rounds towards a = -3
    CHECK_EQ(midpoint(7, 7), 7);
}

TEST(midpoint_does_not_overflow) {
    CHECK_EQ(midpoint(INT_MAX, INT_MAX - 2), INT_MAX - 1);
    CHECK_EQ(midpoint(INT_MIN, INT_MIN + 2), INT_MIN + 1);
    CHECK_EQ(midpoint(INT_MIN, INT_MAX), -1);
    CHECK_EQ(midpoint(INT_MAX, INT_MIN), 0);
}

TEST(powers_of_two) {
    CHECK_EQ(is_power_of_two(0u), false);
    CHECK_EQ(is_power_of_two(1u), true);
    CHECK_EQ(is_power_of_two(2u), true);
    CHECK_EQ(is_power_of_two(3u), false);
    CHECK_EQ(is_power_of_two(1024u), true);
    CHECK_EQ(is_power_of_two(1023u), false);
    CHECK_EQ(is_power_of_two(1u << 31), true);
    CHECK_EQ(is_power_of_two(UINT_MAX), false);
}

TEST(counting_bits) {
    CHECK_EQ(bits_set(0u), 0);
    CHECK_EQ(bits_set(1u), 1);
    CHECK_EQ(bits_set(255u), 8);
    CHECK_EQ(bits_set(0x80000000u), 1);
    CHECK_EQ(bits_set(UINT_MAX), 32);
}

TEST(rounding_up) {
    CHECK_EQ(round_up_to_power_of_two(0u), 1u);
    CHECK_EQ(round_up_to_power_of_two(1u), 1u);
    CHECK_EQ(round_up_to_power_of_two(5u), 8u);
    CHECK_EQ(round_up_to_power_of_two(1024u), 1024u);
    CHECK_EQ(round_up_to_power_of_two(1025u), 2048u);
    CHECK_EQ(round_up_to_power_of_two((1u << 31) - 1), 1u << 31);
}

TEST(last_index_of_a_vector) {
    CHECK_EQ(last_index({}), -1);
    CHECK_EQ(last_index({9}), 0);
    CHECK_EQ(last_index({1, 2, 3, 4}), 3);
}
