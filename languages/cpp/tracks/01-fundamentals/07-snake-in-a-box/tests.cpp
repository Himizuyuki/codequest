#include "mini_test.hpp"

#ifndef SOLUTION
#define SOLUTION "solution.cpp"
#endif
#include SOLUTION

using V = std::vector<int>;
using G = std::vector<std::vector<int>>;

TEST(three_by_three) {
    CHECK_EQ(spiral(G{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}}), (V{1, 2, 3, 6, 9, 8, 7, 4, 5}));
}

TEST(three_by_four) {
    CHECK_EQ(spiral(G{{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}}), (V{1, 2, 3, 4, 8, 12, 11, 10, 9, 5, 6, 7}));
}

TEST(four_by_two) {
    CHECK_EQ(spiral(G{{1, 2}, {3, 4}, {5, 6}, {7, 8}}), (V{1, 2, 4, 6, 8, 7, 5, 3}));
}

TEST(single_cell) {
    CHECK_EQ(spiral(G{{42}}), V{42});
}

TEST(single_row_and_single_column) {
    CHECK_EQ(spiral(G{{1, 2, 3, 4}}), (V{1, 2, 3, 4}));
    CHECK_EQ(spiral(G{{1}, {2}, {3}}), (V{1, 2, 3}));
}

TEST(empty_grids) {
    CHECK_EQ(spiral(G{}), V{});
    CHECK_EQ(spiral(G{{}}), V{});
}

TEST(big_grid_visits_everything_once) {
    const int n = 700;
    G g(n, V(n));
    for (int r = 0; r < n; ++r)
        for (int c = 0; c < n; ++c) g[r][c] = r * n + c;
    V out = spiral(g);
    CHECK_EQ(out.size(), static_cast<std::size_t>(n) * n);
    long long sum = 0;
    for (int x : out) sum += x;
    const long long cells = static_cast<long long>(n) * n;
    CHECK_EQ(sum, cells * (cells - 1) / 2);
    CHECK_EQ(out[n], 2 * n - 1);   // first cell of the right column, below the corner
}
