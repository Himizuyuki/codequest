#include <type_traits>
#include <utility>

#include "mini_test.hpp"

#ifndef SOLUTION
#define SOLUTION "solution.cpp"
#endif
#include SOLUTION

static Buffer make_filled(std::size_t n) {
    Buffer b(n);
    for (std::size_t i = 0; i < b.size(); ++i) b.at(i) = static_cast<int>(i) * 10;
    return b;
}

TEST(construct_zeroed) {
    Buffer b(5);
    CHECK_EQ(b.size(), std::size_t{5});
    CHECK(b.data() != nullptr);
    for (std::size_t i = 0; i < 5; ++i) CHECK_EQ(b.at(i), 0);
}

TEST(empty_buffer) {
    Buffer b(0);
    CHECK_EQ(b.size(), std::size_t{0});
    CHECK_THROWS(b.at(0));
}

TEST(at_reads_writes_and_checks_bounds) {
    Buffer b(3);
    b.at(2) = 42;
    CHECK_EQ(b.at(2), 42);
    const Buffer& view = b;
    CHECK_EQ(view.at(2), 42);
    CHECK_THROWS(b.at(3));
    CHECK_THROWS(view.at(100));
}

TEST(copy_constructor_is_deep) {
    Buffer a = make_filled(4);
    CHECK_EQ(a.size(), std::size_t{4});
    Buffer b(a);
    CHECK_EQ(b.size(), std::size_t{4});
    CHECK(b.data() != a.data());
    CHECK_EQ(b.at(3), 30);
    b.at(3) = -1;
    CHECK_EQ(a.at(3), 30);
}

TEST(move_constructor_steals) {
    Buffer a = make_filled(4);
    CHECK_EQ(a.size(), std::size_t{4});
    const int* memory = a.data();
    Buffer b(std::move(a));
    CHECK_EQ(b.size(), std::size_t{4});
    CHECK(b.data() == memory);
    CHECK_EQ(b.at(2), 20);
    CHECK_EQ(a.size(), std::size_t{0});
    CHECK(a.data() == nullptr);
}

TEST(copy_assignment) {
    Buffer a = make_filled(3);
    Buffer b(10);
    b = a;
    CHECK_EQ(b.size(), std::size_t{3});
    CHECK(b.data() != a.data());
    CHECK_EQ(b.at(2), 20);
    b.at(0) = 99;
    CHECK_EQ(a.at(0), 0);
}

TEST(move_assignment) {
    Buffer a = make_filled(3);
    CHECK_EQ(a.size(), std::size_t{3});
    const int* memory = a.data();
    Buffer b(10);
    b = std::move(a);
    CHECK_EQ(b.size(), std::size_t{3});
    CHECK(b.data() == memory);
    CHECK_EQ(a.size(), std::size_t{0});
    CHECK(a.data() == nullptr);
}

TEST(self_assignment_is_harmless) {
    Buffer a = make_filled(3);
    Buffer& alias = a;
    a = alias;
    CHECK_EQ(a.size(), std::size_t{3});
    CHECK_EQ(a.at(2), 20);
}

TEST(moves_are_noexcept) {
    CHECK(std::is_nothrow_move_constructible_v<Buffer>);
    CHECK(std::is_nothrow_move_assignable_v<Buffer>);
}

TEST(works_inside_a_vector) {
    std::vector<Buffer> v;
    for (std::size_t i = 1; i <= 200; ++i) v.push_back(make_filled(i));
    CHECK_EQ(v.size(), std::size_t{200});
    CHECK_EQ(v[199].size(), std::size_t{200});
    CHECK_EQ(v[199].at(199), 1990);
    std::vector<Buffer> copy = v;
    copy[0].at(0) = 7;
    CHECK_EQ(v[0].at(0), 0);
}
