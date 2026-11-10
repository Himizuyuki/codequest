#include <concepts>
#include <string>
#include <string_view>
#include <vector>

// TODO: integer and floating-point types, but not bool.
template <typename T>
concept Number = true;

template <Number T>
double average(const std::vector<T>& values) {
    // TODO: see problem.md
    return 0.0;
}

// TODO: types with a const name() member whose result converts to std::string.
template <typename T>
concept HasName = true;

std::string greet(const HasName auto& who) {
    // TODO: "Hello, <name>!"
    return "";
}

std::string describe(const auto& value) {
    // TODO: "boolean", "integer", "floating", "text" or "other"
    return "";
}
