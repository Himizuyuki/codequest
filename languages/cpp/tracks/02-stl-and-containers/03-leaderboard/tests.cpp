#include <numeric>
#include <random>

#include "mini_test.hpp"

#ifndef SOLUTION
#define SOLUTION "solution.cpp"
#endif
#include SOLUTION

using Names = std::vector<std::string>;

static Names names(const std::vector<Player>& v) {
    Names out;
    for (const auto& p : v) out.push_back(p.name);
    return out;
}

TEST(empty_and_single) {
    CHECK_EQ(names(rank({})), Names{});
    CHECK_EQ(names(rank({{"solo", 1, 1}})), Names{"solo"});
}

TEST(higher_score_first) {
    auto r = rank({{"ann", 10, 5}, {"bob", 30, 5}, {"cy", 20, 5}});
    CHECK_EQ(names(r), (Names{"bob", "cy", "ann"}));
}

TEST(equal_score_faster_time_first) {
    auto r = rank({{"ann", 10, 300}, {"bob", 10, 100}, {"cy", 10, 200}});
    CHECK_EQ(names(r), (Names{"bob", "cy", "ann"}));
}

TEST(equal_score_and_time_alphabetical) {
    auto r = rank({{"zed", 5, 1}, {"amy", 5, 1}, {"max", 5, 1}});
    CHECK_EQ(names(r), (Names{"amy", "max", "zed"}));
}

TEST(example_from_the_statement) {
    auto r = rank({{"ann", 10, 500}, {"bob", 30, 700}, {"cy", 30, 200}, {"dee", 30, 200}});
    CHECK_EQ(names(r), (Names{"cy", "dee", "bob", "ann"}));
}

TEST(fields_are_kept_with_their_player) {
    auto r = rank({{"low", 1, 9}, {"high", 7, 3}});
    CHECK_EQ(r.size(), std::size_t{2});
    CHECK_EQ(r[0].name, std::string("high"));
    CHECK_EQ(r[0].score, 7);
    CHECK_EQ(r[0].time_ms, 3);
}

TEST(large_random_input) {
    std::mt19937 rng(12345);
    std::vector<Player> players;
    for (int i = 0; i < 100000; ++i)
        players.push_back({"p" + std::to_string(rng() % 5000), static_cast<int>(rng() % 50), static_cast<int>(rng() % 20)});

    auto r = rank(players);
    CHECK_EQ(r.size(), players.size());
    long long before = 0, after = 0;
    for (const auto& p : players) before += p.score;
    for (const auto& p : r) after += p.score;
    CHECK_EQ(after, before);
    for (std::size_t i = 1; i < r.size(); ++i) {
        const auto& a = r[i - 1];
        const auto& b = r[i];
        bool ok = a.score > b.score || (a.score == b.score && (a.time_ms < b.time_ms || (a.time_ms == b.time_ms && a.name <= b.name)));
        CHECK(ok);
    }
}
