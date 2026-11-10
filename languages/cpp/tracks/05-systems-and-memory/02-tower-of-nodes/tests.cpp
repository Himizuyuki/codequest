#include "mini_test.hpp"

#ifndef SOLUTION
#define SOLUTION "solution.cpp"
#endif
#include SOLUTION

TEST(new_stack_is_empty) {
    Stack s;
    CHECK_EQ(s.size(), std::size_t{0});
    CHECK_EQ(s.empty(), true);
    CHECK_THROWS(s.top());
    CHECK_THROWS(s.pop());
}

TEST(push_then_top) {
    Stack s;
    s.push(7);
    CHECK_EQ(s.size(), std::size_t{1});
    CHECK_EQ(s.empty(), false);
    CHECK_EQ(s.top(), 7);
    CHECK_EQ(s.size(), std::size_t{1});   // top does not remove
}

TEST(last_in_first_out) {
    Stack s;
    s.push(1);
    s.push(2);
    s.push(3);
    CHECK_EQ(s.size(), std::size_t{3});
    CHECK_EQ(s.pop(), 3);
    CHECK_EQ(s.pop(), 2);
    CHECK_EQ(s.top(), 1);
    CHECK_EQ(s.size(), std::size_t{1});
    CHECK_EQ(s.pop(), 1);
    CHECK_EQ(s.empty(), true);
    CHECK_THROWS(s.pop());
}

TEST(reuse_after_emptying) {
    Stack s;
    s.push(5);
    CHECK_EQ(s.pop(), 5);
    s.push(6);
    s.push(7);
    CHECK_EQ(s.pop(), 7);
    CHECK_EQ(s.pop(), 6);
}

TEST(many_pushes_and_pops) {
    Stack s;
    for (int i = 0; i < 100000; ++i) s.push(i);
    CHECK_EQ(s.size(), std::size_t{100000});
    long long sum = 0;
    while (!s.empty() && s.size() <= 100000) sum += s.pop();
    CHECK_EQ(sum, 4999950000LL);
}

TEST(two_million_nodes_destroyed_at_scope_exit) {
    std::size_t size_before_exit = 0;
    {
        Stack s;
        for (int i = 0; i < 2000000; ++i) s.push(i);
        size_before_exit = s.size();
    }   // <- the destructor runs here; a recursive one overflows the call stack
    CHECK_EQ(size_before_exit, std::size_t{2000000});
}
