#include <algorithm>

#include "mini_test.hpp"

#ifndef SOLUTION
#define SOLUTION "solution.cpp"
#endif
#include SOLUTION

using G = std::vector<std::vector<std::string>>;
using W = std::vector<std::string>;

TEST(empty_input) {
    CHECK_EQ(group_anagrams({}), G{});
}

TEST(single_word) {
    CHECK_EQ(group_anagrams({"solo"}), (G{{"solo"}}));
}

TEST(classic_example) {
    CHECK_EQ(group_anagrams({"eat", "tea", "tan", "ate", "nat", "bat"}),
             (G{{"ate", "eat", "tea"}, {"bat"}, {"nat", "tan"}}));
}

TEST(duplicates_are_kept) {
    CHECK_EQ(group_anagrams({"a", "a", "b"}), (G{{"a", "a"}, {"b"}}));
}

TEST(no_anagrams) {
    CHECK_EQ(group_anagrams({"cat", "dog", "bird"}), (G{{"bird"}, {"cat"}, {"dog"}}));
}

TEST(many_words) {
    // Every word is a rotation of "abcdefgh": all one big group.
    W words;
    std::string base = "abcdefgh";
    for (int i = 0; i < 20000; ++i) {
        std::rotate(base.begin(), base.begin() + (i % 8), base.end());
        words.push_back(base);
    }
    G got = group_anagrams(words);
    CHECK_EQ(got.size(), std::size_t{1});
    CHECK_EQ(got[0].size(), std::size_t{20000});
}
