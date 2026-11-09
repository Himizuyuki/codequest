// mini_test.hpp - a tiny single-header test framework for CodeQuest.
//
// Each tests.cpp is its own program: it includes this header, includes the
// learner's solution, declares TESTs, and gets a main() for free.
#pragma once

#include <exception>
#include <functional>
#include <iostream>
#include <ranges>
#include <sstream>
#include <string>
#include <string_view>
#include <type_traits>
#include <vector>

namespace mt {

struct Failure {
    std::string msg;
};

struct Case {
    std::string name;
    std::function<void()> fn;
};

inline std::vector<Case>& registry() {
    static std::vector<Case> cases;
    return cases;
}

struct Registrar {
    Registrar(std::string name, std::function<void()> fn) {
        registry().push_back({std::move(name), std::move(fn)});
    }
};

// Pretty-printer used in failure messages: strings, ranges and pairs.
template <class T>
std::string show(const T& v) {
    std::ostringstream os;
    if constexpr (std::is_convertible_v<const T&, std::string_view>) {
        os << '"' << std::string_view(v) << '"';
    } else if constexpr (requires { os << v; }) {
        os << v;
    } else if constexpr (requires { v.has_value(); *v; }) {
        if (v.has_value()) os << "some(" << show(*v) << ')';
        else os << "nullopt";
    } else if constexpr (std::ranges::range<T>) {
        os << '[';
        bool first = true;
        for (const auto& x : v) {
            if (!first) os << ", ";
            first = false;
            os << show(x);
        }
        os << ']';
    } else if constexpr (requires { v.first; v.second; }) {
        os << '(' << show(v.first) << ", " << show(v.second) << ')';
    } else {
        os << "<unprintable>";
    }
    return os.str();
}

}  // namespace mt

#define TEST(name)                                           \
    static void name();                                      \
    static mt::Registrar mt_registrar_##name{#name, name};   \
    static void name()

#define CHECK(cond)                                                                    \
    do {                                                                               \
        if (!(cond))                                                                   \
            throw mt::Failure{"line " + std::to_string(__LINE__) + ": CHECK(" #cond ") failed"}; \
    } while (0)

#define CHECK_EQ(actual, expected)                                                     \
    do {                                                                               \
        const auto& mt_a = (actual);                                                   \
        const auto& mt_e = (expected);                                                 \
        if (!(mt_a == mt_e))                                                           \
            throw mt::Failure{"line " + std::to_string(__LINE__) + ": " #actual        \
                              "\n        got:      " + mt::show(mt_a) +                 \
                              "\n        expected: " + mt::show(mt_e)};                 \
    } while (0)

int main() {
    int passed = 0, failed = 0;
    for (const auto& c : mt::registry()) {
        try {
            c.fn();
            ++passed;
            std::cout << "  PASS  " << c.name << '\n';
        } catch (const mt::Failure& f) {
            ++failed;
            std::cout << "  FAIL  " << c.name << "\n        " << f.msg << '\n';
        } catch (const std::exception& e) {
            ++failed;
            std::cout << "  FAIL  " << c.name << "\n        threw: " << e.what() << '\n';
        }
    }
    std::cout << '\n' << passed << '/' << passed + failed << " tests passed\n";
    return failed == 0 ? 0 : 1;
}
