#include <array>
#include <string>

#include "mini_test.hpp"

#ifndef SOLUTION
#define SOLUTION "solution.cpp"
#endif
#include SOLUTION

using SV = std::string_view;
using Parts = std::vector<std::string_view>;

TEST(trim_both_ends) {
    CHECK_EQ(trim("  hi there \t"), SV("hi there"));
    CHECK_EQ(trim("word"), SV("word"));
    CHECK_EQ(trim("\t\tx"), SV("x"));
}

TEST(trim_empty_and_blank) {
    CHECK_EQ(trim("").size(), std::size_t{0});
    CHECK_EQ(trim("   \t ").size(), std::size_t{0});
}

TEST(trim_returns_a_view_into_the_input) {
    std::string text = "  hello  ";
    SV t = trim(text);
    CHECK_EQ(t, SV("hello"));
    CHECK(t.data() == text.data() + 2);
}

TEST(split_keeps_empty_fields) {
    CHECK_EQ(split("a,b,,c", ','), (Parts{"a", "b", "", "c"}));
    CHECK_EQ(split("a,", ','), (Parts{"a", ""}));
    CHECK_EQ(split(",a", ','), (Parts{"", "a"}));
}

TEST(split_without_separator) {
    CHECK_EQ(split("abc", ','), (Parts{"abc"}));
    CHECK_EQ(split("", ','), (Parts{""}));
}

TEST(split_returns_views_into_the_input) {
    std::string text = "key=value";
    Parts parts = split(text, '=');
    CHECK_EQ(parts.size(), std::size_t{2});
    CHECK(parts[0].data() == text.data());
    CHECK(parts[1].data() == text.data() + 4);
    CHECK_EQ(parts[1], SV("value"));
}

TEST(commands) {
    CHECK_EQ(is_command("/help"), true);
    CHECK_EQ(is_command("   /quit now"), true);
    CHECK_EQ(is_command("hello /help"), false);
    CHECK_EQ(is_command(""), false);
    CHECK_EQ(is_command("   "), false);
}

TEST(sum_accepts_any_contiguous_container) {
    std::vector<int> vec{1, 2, 3};
    std::array<int, 4> arr{10, 20, 30, 40};
    int raw[] = {5, 5};
    CHECK_EQ(sum(vec), 6LL);
    CHECK_EQ(sum(arr), 100LL);
    CHECK_EQ(sum(raw), 10LL);
    CHECK_EQ(sum(std::span<const int>{}), 0LL);
    CHECK_EQ(sum(std::span<const int>(vec).subspan(1)), 5LL);
}

TEST(sum_does_not_overflow) {
    std::vector<int> big(1000000, 2000000000);
    CHECK_EQ(sum(big), 2000000000000000LL);
}

TEST(longest_run_points_into_the_input) {
    std::vector<int> v{1, 2, -1, 3, 4, 5, 0, 6};
    auto run = longest_positive_run(v);
    CHECK_EQ(run.size(), std::size_t{3});
    CHECK(run.data() == v.data() + 3);
    CHECK_EQ(run[0], 3);
    CHECK_EQ(run[2], 5);
}

TEST(longest_run_first_wins_on_ties) {
    std::vector<int> v{7, 8, 0, 9, 9};
    auto run = longest_positive_run(v);
    CHECK_EQ(run.size(), std::size_t{2});
    CHECK(run.data() == v.data());
}

TEST(longest_run_edge_cases) {
    std::vector<int> none{-1, 0, -3};
    CHECK_EQ(longest_positive_run(none).size(), std::size_t{0});
    CHECK_EQ(longest_positive_run(std::span<const int>{}).size(), std::size_t{0});
    std::vector<int> all{4, 5, 6};
    CHECK_EQ(longest_positive_run(all).size(), std::size_t{3});
    std::vector<int> tail{0, 0, 1, 2, 3, 4};
    auto run = longest_positive_run(tail);
    CHECK_EQ(run.size(), std::size_t{4});
    CHECK(run.data() == tail.data() + 2);
}
