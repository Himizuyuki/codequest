// mini_test.hpp - a tiny single-header test framework for CodeQuest.
//
// Each tests.cpp is its own program: it includes this header, includes the
// learner's solution, declares TESTs, and gets a main() for free.
#pragma once

#include <cstddef>
#include <exception>
#include <fstream>
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

// ---------------------------------------------------------------------------
// Pretty-printer used in failure messages and by SHOW().
// Strings are quoted with invisible characters escaped ("a\n", "tab\there"), so a
// stray space or newline is visible. Long values are shortened.
// ---------------------------------------------------------------------------
inline constexpr std::size_t max_shown_chars = 300;
inline constexpr std::size_t max_shown_items = 30;

inline void escape_into(std::string& out, char ch) {
    switch (ch) {
        case '\n': out += "\\n"; break;
        case '\t': out += "\\t"; break;
        case '\r': out += "\\r"; break;
        case '\0': out += "\\0"; break;
        case '\\': out += "\\\\"; break;
        default:
            if (static_cast<unsigned char>(ch) < 32 || ch == 127) {
                static const char* hex = "0123456789abcdef";
                out += "\\x";
                out += hex[(static_cast<unsigned char>(ch) >> 4) & 15];
                out += hex[static_cast<unsigned char>(ch) & 15];
            } else {
                out += ch;
            }
    }
}

inline std::string quoted(std::string_view sv) {
    std::string out = "\"";
    for (char ch : sv.substr(0, max_shown_chars)) {
        if (ch == '"') out += "\\\"";
        else escape_into(out, ch);
    }
    out += '"';
    if (sv.size() > max_shown_chars) out += "... (" + std::to_string(sv.size()) + " chars in total)";
    return out;
}

template <class T>
concept StringLike = std::is_convertible_v<const T&, std::string_view>;

template <class T>
std::string show(const T& v) {
    std::ostringstream os;
    if constexpr (StringLike<T>) {
        return quoted(std::string_view(v));
    } else if constexpr (std::is_same_v<T, bool>) {
        os << (v ? "true" : "false");
    } else if constexpr (std::is_same_v<T, char>) {
        std::string out = "'";
        if (v == '\'') out += "\\'";
        else escape_into(out, v);
        return out + "'";
    } else if constexpr (std::is_same_v<T, signed char> || std::is_same_v<T, unsigned char>) {
        os << static_cast<int>(v);                       // int8_t / uint8_t are numbers here
    } else if constexpr (requires { os << v; }) {
        os << v;
    } else if constexpr (requires { v.has_value(); *v; }) {
        if (v.has_value()) os << "some(" << show(*v) << ')';
        else os << "nullopt";
    } else if constexpr (std::ranges::range<const T&>) {
        os << '[';
        std::size_t n = 0;
        for (const auto& x : v) {
            if (n == max_shown_items) break;
            if (n++) os << ", ";
            os << show(x);
        }
        const auto total = static_cast<std::size_t>(std::ranges::distance(v));
        if (total > max_shown_items) os << ", ... (" << total << " elements in total)";
        os << ']';
    } else if constexpr (requires { v.first; v.second; }) {
        os << '(' << show(v.first) << ", " << show(v.second) << ')';
    } else {
        os << "<a value this framework cannot print>";
    }
    return os.str();
}

// Extra help when two strings or two sequences differ: where is the first difference?
template <class A, class E>
std::string explain(const A& got, const E& expected) {
    const std::string pad = "\n        ";
    if constexpr (StringLike<A> && StringLike<E>) {
        const std::string_view g(got), e(expected);
        std::size_t i = 0;
        while (i < g.size() && i < e.size() && g[i] == e[i]) ++i;
        std::string out;
        if (g.size() != e.size())
            out += pad + "lengths:    got " + std::to_string(g.size()) + ", expected " + std::to_string(e.size());
        out += pad + "first difference at position " + std::to_string(i) + ": got " +
               (i < g.size() ? show(g[i]) : std::string("<end of string>")) + ", expected " +
               (i < e.size() ? show(e[i]) : std::string("<end of string>"));
        if (i > 20) {                                    // long strings: show the neighbourhood too
            const std::size_t from = i - 10;
            out += pad + "around it:  got      ..." + quoted(g.substr(from, 40)) +
                   pad + "            expected ..." + quoted(e.substr(from, 40));
        }
        return out;
    } else if constexpr (std::ranges::forward_range<const A&> && std::ranges::forward_range<const E&> &&
                         requires(const A& a, const E& e) { *std::ranges::begin(a) == *std::ranges::begin(e); }) {
        const auto gn = static_cast<std::size_t>(std::ranges::distance(got));
        const auto en = static_cast<std::size_t>(std::ranges::distance(expected));
        auto g = std::ranges::begin(got);
        auto e = std::ranges::begin(expected);
        std::size_t i = 0;
        while (i < gn && i < en && *g == *e) { ++g; ++e; ++i; }
        std::string out;
        if (gn != en) out += pad + "sizes:      got " + std::to_string(gn) + ", expected " + std::to_string(en);
        if (i < gn || i < en)
            out += pad + "first difference at index " + std::to_string(i) + ": got " +
                   (i < gn ? show(*g) : std::string("<nothing>")) + ", expected " +
                   (i < en ? show(*e) : std::string("<nothing>"));
        return out;
    } else {
        return "";
    }
}

// "tests.cpp:42" plus the text of that source line, when the file can be read.
inline std::string where(const char* file, int line) {
    std::string name = file;
    if (const auto slash = name.find_last_of('/'); slash != std::string::npos) name = name.substr(slash + 1);
    std::string out = name + ":" + std::to_string(line);
    std::ifstream in(file);
    std::string text;
    for (int i = 0; i < line && std::getline(in, text); ++i) {}
    if (in) {
        const auto first = text.find_first_not_of(" \t");
        if (first != std::string::npos) out += "\n        > " + text.substr(first);
    }
    return out;
}

}  // namespace mt

#define TEST(name)                                           \
    static void name();                                      \
    static mt::Registrar mt_registrar_##name{#name, name};   \
    static void name()

// A failed check stops its TEST (later lines may depend on it); the other TESTs still run.
#define CHECK(cond)                                                                    \
    do {                                                                               \
        if (!(cond))                                                                   \
            throw mt::Failure{mt::where(__FILE__, __LINE__) +                          \
                              "\n        this condition is false: " #cond};            \
    } while (0)

#define CHECK_THROWS(expr)                                                             \
    do {                                                                               \
        bool mt_threw = false;                                                         \
        try {                                                                          \
            (void)(expr);                                                              \
        } catch (...) {                                                                \
            mt_threw = true;                                                           \
        }                                                                              \
        if (!mt_threw)                                                                 \
            throw mt::Failure{mt::where(__FILE__, __LINE__) +                          \
                              "\n        expected an exception from: " #expr           \
                              "\n        but it returned normally"};                   \
    } while (0)

#define CHECK_EQ(actual, expected)                                                     \
    do {                                                                               \
        const auto& mt_a = (actual);                                                   \
        const auto& mt_e = (expected);                                                 \
        if (!(mt_a == mt_e))                                                           \
            throw mt::Failure{mt::where(__FILE__, __LINE__) +                          \
                              "\n        expression: " #actual                         \
                              "\n        got:        " + mt::show(mt_a) +              \
                              "\n        expected:   " + mt::show(mt_e) +              \
                              mt::explain(mt_a, mt_e)};                                \
    } while (0)

// Prints an expression and its value - for exploring in my_tests.cpp. Never fails.
#define SHOW(expr)                                                                     \
    do {                                                                               \
        const auto& mt_v = (expr);                                                     \
        std::cout << "        " #expr " = " << mt::show(mt_v) << std::endl;            \
    } while (0)

// Define MINI_TEST_NO_MAIN before including this header to write your own main().
#ifndef MINI_TEST_NO_MAIN
// Arguments, if any, select tests: only those whose name contains one of them run.
int main(int argc, char** argv) {
    int passed = 0, failed = 0, skipped = 0;
    std::vector<std::string> failures;
    for (const auto& c : mt::registry()) {
        bool wanted = argc < 2;
        for (int i = 1; i < argc; ++i) wanted = wanted || c.name.find(argv[i]) != std::string::npos;
        if (!wanted) { ++skipped; continue; }
        std::string problem;
        try {
            c.fn();
        } catch (const mt::Failure& f) {
            problem = f.msg;
        } catch (const std::exception& e) {
            problem = std::string("an exception escaped from the test: ") + e.what();
        } catch (...) {
            problem = "an exception of an unknown type escaped from the test";
        }
        if (problem.empty()) {
            ++passed;
            std::cout << "  PASS  " << c.name << std::endl;
        } else {
            ++failed;
            failures.push_back(c.name);
            std::cout << "  FAIL  " << c.name << "\n        " << problem << '\n' << std::endl;
        }
    }
    if (!failures.empty()) {
        std::cout << "\nFailed:";
        for (const auto& name : failures) std::cout << ' ' << name;
        std::cout << '\n';
    }
    if (skipped) std::cout << "\n(" << skipped << " tests skipped by the filter)";
    std::cout << '\n' << passed << '/' << passed + failed << " tests passed\n";
    if (passed + failed == 0) { std::cout << "No test matched.\n"; return 1; }
    return failed == 0 ? 0 : 1;
}
#endif
