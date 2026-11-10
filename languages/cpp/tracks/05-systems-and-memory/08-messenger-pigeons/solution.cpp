#include <cstdio>
#include <functional>
#include <string>
#include <vector>

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int run_child(const std::function<int()>& child_main) {
    // TODO: see problem.md
    (void)child_main;
    return -1;
}

std::string capture(const std::function<void()>& child_main) {
    // TODO: see problem.md
    (void)child_main;
    return "<not implemented>";
}

struct Result {
    int status;
    std::string out;
};

Result run_program(const std::vector<std::string>& argv) {
    // TODO: see problem.md
    (void)argv;
    return {-1, ""};
}
