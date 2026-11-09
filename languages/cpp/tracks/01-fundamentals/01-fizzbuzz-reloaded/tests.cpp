#include "mini_test.hpp"

#ifndef SOLUTION
#define SOLUTION "solution.cpp"
#endif
#include SOLUTION

using V = std::vector<std::string>;

// The message for number i, taken from fizzbuzz_reloaded(i). Checks the size
// first so an unfinished solution fails cleanly instead of reading out of bounds.
static std::string message_for(int i) {
    V r = fizzbuzz_reloaded(i);
    CHECK_EQ(r.size(), static_cast<std::size_t>(i));
    return r.back();
}

TEST(zero_gives_empty) {
    CHECK_EQ(fizzbuzz_reloaded(0), V{});
}

TEST(first_five) {
    CHECK_EQ(fizzbuzz_reloaded(5), (V{"1", "2", "Fizz", "4", "Buzz"}));
}

TEST(zap_appears_at_seven) {
    CHECK_EQ(message_for(7), std::string("Zap"));
}

TEST(classic_fizzbuzz_at_fifteen) {
    CHECK_EQ(message_for(15), std::string("FizzBuzz"));
}

TEST(combinations) {
    CHECK_EQ(message_for(21), std::string("FizzZap"));
    CHECK_EQ(message_for(35), std::string("BuzzZap"));
    CHECK_EQ(message_for(105), std::string("FizzBuzzZap"));
}

TEST(plain_numbers_stay_numbers) {
    CHECK_EQ(message_for(11), std::string("11"));
    CHECK_EQ(message_for(22), std::string("22"));
}
