#include <cctype>
#include <compare>
#include <cstddef>
#include <string>

struct Date {
    int year;
    int month;
    int day;

    // TODO: these two placeholders are wrong. Replace BOTH with one defaulted operator<=>.
    std::strong_ordering operator<=>(const Date&) const { return std::strong_ordering::equal; }
    bool operator==(const Date&) const { return false; }
};

std::string relation(const Date& a, const Date& b) {
    // TODO: "before", "same" or "after"
    return "";
}

struct CaseInsensitive {
    std::string text;

    // TODO: compare ignoring case (see problem.md)
    std::weak_ordering operator<=>(const CaseInsensitive& other) const { return std::weak_ordering::equivalent; }
    bool operator==(const CaseInsensitive& other) const { return false; }
};
