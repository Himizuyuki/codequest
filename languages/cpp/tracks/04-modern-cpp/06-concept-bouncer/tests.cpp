#include <cmath>

#include "mini_test.hpp"

#ifndef SOLUTION
#define SOLUTION "solution.cpp"
#endif
#include SOLUTION

using S = std::string;

struct Robot {
    std::string name() const { return "R2"; }
};
struct Cat {
    const char* name() const { return "Tom"; }   // converts to std::string: fine
};
struct Rock {};
struct Liar {
    int name() const { return 7; }               // has name(), but it is not text
};

template <typename T>
concept CanAverage = requires(const std::vector<T>& v) { average(v); };

template <typename T>
concept CanGreet = requires(const T& t) { greet(t); };

TEST(number_accepts_numbers) {
    CHECK_EQ(Number<int>, true);
    CHECK_EQ(Number<long long>, true);
    CHECK_EQ(Number<unsigned char>, true);
    CHECK_EQ(Number<float>, true);
    CHECK_EQ(Number<double>, true);
}

TEST(number_rejects_everything_else) {
    CHECK_EQ(Number<bool>, false);
    CHECK_EQ(Number<std::string>, false);
    CHECK_EQ(Number<const char*>, false);
    CHECK_EQ(Number<std::vector<int>>, false);
}

TEST(average_values) {
    CHECK_EQ(average(std::vector<int>{1, 2}), 1.5);
    CHECK_EQ(average(std::vector<int>{4}), 4.0);
    CHECK_EQ(average(std::vector<double>{0.5, 1.5, 4.0}), 2.0);
    CHECK_EQ(average(std::vector<int>{}), 0.0);
}

TEST(average_does_not_overflow) {
    CHECK_EQ(average(std::vector<int>{2000000000, 2000000000}), 2000000000.0);
}

TEST(average_is_constrained) {
    CHECK_EQ(CanAverage<int>, true);
    CHECK_EQ(CanAverage<double>, true);
    CHECK_EQ(CanAverage<std::string>, false);
    CHECK_EQ(CanAverage<bool>, false);
}

TEST(has_name) {
    CHECK_EQ(HasName<Robot>, true);
    CHECK_EQ(HasName<Cat>, true);
    CHECK_EQ(HasName<Rock>, false);
    CHECK_EQ(HasName<int>, false);
    CHECK_EQ(HasName<Liar>, false);
}

TEST(greeting) {
    CHECK_EQ(greet(Robot{}), S("Hello, R2!"));
    CHECK_EQ(greet(Cat{}), S("Hello, Tom!"));
    CHECK_EQ(CanGreet<Robot>, true);
    CHECK_EQ(CanGreet<Rock>, false);
}

TEST(describe_numbers) {
    CHECK_EQ(describe(42), S("integer"));
    CHECK_EQ(describe(42u), S("integer"));
    CHECK_EQ(describe(7LL), S("integer"));
    CHECK_EQ(describe(3.14), S("floating"));
    CHECK_EQ(describe(2.5f), S("floating"));
}

TEST(describe_bool_and_char) {
    CHECK_EQ(describe(true), S("boolean"));
    CHECK_EQ(describe('c'), S("integer"));   // char is an integral type!
}

TEST(describe_text_and_other) {
    CHECK_EQ(describe("hi"), S("text"));
    CHECK_EQ(describe(std::string("hi")), S("text"));
    CHECK_EQ(describe(std::string_view("hi")), S("text"));
    CHECK_EQ(describe(std::vector<int>{1}), S("other"));
    CHECK_EQ(describe(Rock{}), S("other"));
}
