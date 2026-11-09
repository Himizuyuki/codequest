#include <string>

#include "mini_test.hpp"

#ifndef SOLUTION
#define SOLUTION "solution.cpp"
#endif
#include SOLUTION

using S = std::string;

TEST(encode_empty_and_single) {
    CHECK_EQ(rle_encode(""), S(""));
    CHECK_EQ(rle_encode("a"), S("a1"));
}

TEST(encode_example) {
    CHECK_EQ(rle_encode("aaabccdddd"), S("a3b1c2d4"));
}

TEST(encode_multi_digit_counts) {
    CHECK_EQ(rle_encode(S(12, 'x')), S("x12"));
    CHECK_EQ(rle_encode(S(100, 'q') + "r"), S("q100r1"));
}

TEST(encode_case_matters) {
    CHECK_EQ(rle_encode("aAaA"), S("a1A1a1A1"));
}

TEST(decode_examples) {
    CHECK_EQ(rle_decode("a3b1"), S("aaab"));
    CHECK_EQ(rle_decode("z10"), S("zzzzzzzzzz"));
    CHECK_EQ(rle_decode(""), S(""));
}

TEST(roundtrip_small) {
    for (const S& s : {S("a"), S("ab"), S("aabbcc"), S("abcabc"), S("zzzzzzzzzzzzzzzzzzzz"), S("QQQwwwEEErrrTTTyyy")}) {
        CHECK_EQ(rle_decode(rle_encode(s)), s);
    }
}

TEST(million_characters) {
    S big = S(500000, 'a') + S(500000, 'b');
    CHECK_EQ(rle_encode(big), S("a500000b500000"));
    CHECK_EQ(rle_decode("a500000b500000"), big);
}
