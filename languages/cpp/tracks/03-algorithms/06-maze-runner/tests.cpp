#include "mini_test.hpp"

#ifndef SOLUTION
#define SOLUTION "solution.cpp"
#endif
#include SOLUTION

using G = std::vector<std::string>;

TEST(next_to_each_other) {
    CHECK_EQ(shortest_path(G{"SE"}), 1);
    CHECK_EQ(shortest_path(G{"E", "S"}), 1);
}

TEST(straight_line) {
    CHECK_EQ(shortest_path(G{"S.E"}), 2);
    CHECK_EQ(shortest_path(G{"S....E"}), 5);
}

TEST(around_a_wall) {
    CHECK_EQ(shortest_path(G{"S#E",
                             ".#.",
                             "..."}), 6);
}

TEST(long_way_round) {
    CHECK_EQ(shortest_path(G{"S...",
                             "###.",
                             "E..."}), 8);
}

TEST(no_way_out) {
    CHECK_EQ(shortest_path(G{"S#E"}), -1);
    CHECK_EQ(shortest_path(G{"S.#",
                             "###",
                             "..E"}), -1);
}

TEST(shortest_not_just_any_path) {
    // Two routes: 12 moves around the block, or 4 straight down.
    CHECK_EQ(shortest_path(G{"S....",
                             ".###.",
                             ".###.",
                             ".###.",
                             "E...."}), 4);
}

TEST(big_open_maze) {
    G g(1000, std::string(1000, '.'));
    g[0][0] = 'S';
    g[999][999] = 'E';
    CHECK_EQ(shortest_path(g), 1998);
}

TEST(big_maze_with_a_closed_door) {
    G g(1000, std::string(1000, '.'));
    g[0][0] = 'S';
    g[999][999] = 'E';
    g[500] = std::string(1000, '#');
    CHECK_EQ(shortest_path(g), -1);
}
