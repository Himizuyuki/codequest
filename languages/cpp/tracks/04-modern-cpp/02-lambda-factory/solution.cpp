#include <functional>
#include <utility>
#include <vector>

std::function<int()> make_counter(int start) {
    // TODO: see problem.md
    return [] { return 0; };
}

std::function<int(int)> make_multiplier(int k) {
    // TODO: see problem.md
    return [](int) { return 0; };
}

std::vector<std::function<int(int)>> make_adders(int n) {
    // TODO: see problem.md
    return {};
}

std::function<int(int)> compose(std::function<int(int)> f, std::function<int(int)> g) {
    // TODO: see problem.md
    return [](int) { return 0; };
}

int apply_n(const std::function<int(int)>& f, int times, int x) {
    // TODO: see problem.md
    return 0;
}
