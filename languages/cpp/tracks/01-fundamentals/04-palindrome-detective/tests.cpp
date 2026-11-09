#include <string>

#include "mini_test.hpp"

#ifndef SOLUTION
#define SOLUTION "solution.cpp"
#endif
#include SOLUTION

TEST(classic_palindromes) {
    CHECK_EQ(is_palindrome("A man, a plan, a canal: Panama"), true);
    CHECK_EQ(is_palindrome("No 'x' in Nixon"), true);
    CHECK_EQ(is_palindrome("Madam, I'm Adam"), true);
}

TEST(not_palindromes) {
    CHECK_EQ(is_palindrome("race a car"), false);
    CHECK_EQ(is_palindrome("hello"), false);
}

TEST(empty_and_punctuation_only) {
    CHECK_EQ(is_palindrome(""), true);
    CHECK_EQ(is_palindrome(" "), true);
    CHECK_EQ(is_palindrome(".,!"), true);
}

TEST(digits_and_letters_are_different) {
    CHECK_EQ(is_palindrome("0P"), false);
    CHECK_EQ(is_palindrome("12321"), true);
}

TEST(underscore_is_ignored) {
    CHECK_EQ(is_palindrome("ab_a"), true);
}

TEST(million_characters) {
    std::string big(1000000, 'a');
    CHECK_EQ(is_palindrome(big), true);
    big[10] = 'b';
    CHECK_EQ(is_palindrome(big), false);
}

TEST(almost_already_palindromes) {
    CHECK_EQ(almost_palindrome(""), true);
    CHECK_EQ(almost_palindrome("a"), true);
    CHECK_EQ(almost_palindrome("aba"), true);
}

TEST(almost_one_deletion) {
    CHECK_EQ(almost_palindrome("abca"), true);
    CHECK_EQ(almost_palindrome("deeee"), true);
    CHECK_EQ(almost_palindrome("eccer"), true);
    CHECK_EQ(almost_palindrome("abcdba"), true);
}

TEST(almost_needs_two_deletions) {
    CHECK_EQ(almost_palindrome("abc"), false);
    CHECK_EQ(almost_palindrome("abcdefdba"), false);
}

TEST(almost_is_exact_not_tidy) {
    // Unlike is_palindrome, case and punctuation count here.
    CHECK_EQ(almost_palindrome("Aba"), false);   // 'A' != 'a', and no single deletion fixes it
    CHECK_EQ(almost_palindrome("a,ba"), true);   // delete the comma
}

TEST(almost_large_inputs) {
    std::string good = std::string(50000, 'a') + "bc" + std::string(50000, 'a');
    CHECK_EQ(almost_palindrome(good), true);
    std::string bad = std::string(50000, 'a') + "bcd" + std::string(50000, 'a');
    CHECK_EQ(almost_palindrome(bad), false);
}
