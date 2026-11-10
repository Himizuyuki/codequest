#include <algorithm>
#include <compare>

#include "mini_test.hpp"

#ifndef SOLUTION
#define SOLUTION "solution.cpp"
#endif
#include SOLUTION

using S = std::string;
using CI = CaseInsensitive;

static Date D(int y, int m, int d) { return Date{y, m, d}; }

TEST(date_equality) {
    CHECK_EQ(D(2024, 5, 1) == D(2024, 5, 1), true);
    CHECK_EQ(D(2024, 5, 1) != D(2024, 5, 2), true);
    CHECK_EQ(D(2024, 5, 1) == D(2023, 5, 1), false);
}

TEST(date_ordering_by_day_month_year) {
    CHECK_EQ(D(2024, 5, 1) < D(2024, 5, 2), true);
    CHECK_EQ(D(2024, 5, 31) < D(2024, 6, 1), true);
    CHECK_EQ(D(2023, 12, 31) < D(2024, 1, 1), true);
    CHECK_EQ(D(2024, 1, 1) > D(2023, 12, 31), true);
    CHECK_EQ(D(2024, 1, 1) <= D(2024, 1, 1), true);
    CHECK_EQ(D(2024, 1, 2) >= D(2024, 1, 3), false);
}

TEST(date_three_way_result) {
    CHECK_EQ(std::is_lt(Date{2020, 1, 1} <=> Date{2021, 1, 1}), true);
    CHECK_EQ(std::is_eq(Date{2020, 1, 1} <=> Date{2020, 1, 1}), true);
    CHECK_EQ(std::is_gt(Date{2020, 2, 1} <=> Date{2020, 1, 31}), true);
}

TEST(dates_sort) {
    std::vector<Date> d{{2024, 3, 9}, {2021, 12, 25}, {2024, 3, 1}, {2022, 1, 1}};
    std::ranges::sort(d);
    std::vector<int> years, days;
    for (const auto& x : d) {
        years.push_back(x.year);
        days.push_back(x.day);
    }
    CHECK_EQ(years, (std::vector<int>{2021, 2022, 2024, 2024}));
    CHECK_EQ(days, (std::vector<int>{25, 1, 1, 9}));
}

TEST(relation_words) {
    CHECK_EQ(relation({2024, 1, 1}, {2023, 6, 1}), S("after"));
    CHECK_EQ(relation({2023, 6, 1}, {2024, 1, 1}), S("before"));
    CHECK_EQ(relation({2024, 2, 29}, {2024, 2, 29}), S("same"));
}

TEST(case_insensitive_equality) {
    CHECK_EQ(CI{"Hello"} == CI{"HELLO"}, true);
    CHECK_EQ(CI{"Hello"} != CI{"Help"}, true);
    CHECK_EQ(CI{""} == CI{""}, true);
    CHECK_EQ(CI{"a"} == CI{"ab"}, false);
}

TEST(case_insensitive_ordering) {
    CHECK_EQ(CI{"apple"} < CI{"Banana"}, true);
    CHECK_EQ(CI{"Banana"} < CI{"apple"}, false);
    CHECK_EQ(CI{"app"} < CI{"APPLE"}, true);
    CHECK_EQ(CI{"zebra"} > CI{"Yak"}, true);
    CHECK_EQ(CI{"same"} <= CI{"SAME"}, true);
    CHECK_EQ(std::is_eq(CI{"MiXeD"} <=> CI{"mixed"}), true);
}

TEST(case_insensitive_sort) {
    std::vector<CI> words{{"pear"}, {"Apple"}, {"banana"}, {"Cherry"}};
    std::sort(words.begin(), words.end());
    std::vector<S> out;
    for (const auto& w : words) out.push_back(w.text);
    CHECK_EQ(out, (std::vector<S>{"Apple", "banana", "Cherry", "pear"}));
}
