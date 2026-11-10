#include <cerrno>
#include <csignal>
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

#include <sys/wait.h>
#include <unistd.h>

#include "mini_test.hpp"

#ifndef SOLUTION
#define SOLUTION "solution.cpp"
#endif
#include SOLUTION

static const pid_t test_pid = getpid();

// A child process that escapes from the solution (it returned instead of calling _exit) is stopped here,
// with a status the parent will not expect.
static void only_the_parent_gets_here() {
    if (getpid() != test_pid) _exit(99);
}

// True if every child has been waited for.
static bool no_children_left() {
    int status = 0;
    errno = 0;
    return waitpid(-1, &status, WNOHANG) == -1 && errno == ECHILD;
}

static int child(const std::function<int()>& f) {
    const int r = run_child(f);
    only_the_parent_gets_here();
    return r;
}

static std::string cap(const std::function<void()>& f) {
    std::string r = capture(f);
    only_the_parent_gets_here();
    return r;
}

static Result prog(const std::vector<std::string>& argv) {
    Result r = run_program(argv);
    only_the_parent_gets_here();
    return r;
}

static void say(const char* text) {
    const std::string s(text);
    std::size_t done = 0;
    while (done < s.size()) {
        const ssize_t n = write(STDOUT_FILENO, s.data() + done, s.size() - done);
        if (n <= 0) return;
        done += static_cast<std::size_t>(n);
    }
}

static int shared_number = 1;

TEST(child_exit_code) {
    CHECK_EQ(child([] { return 0; }), 0);
    CHECK_EQ(child([] { return 7; }), 7);
    CHECK_EQ(child([] { return 255; }), 255);
    CHECK(no_children_left());
}

TEST(exit_codes_are_eight_bits) {
    CHECK_EQ(child([] { return 300; }), 44);
    CHECK_EQ(child([] { return -1; }), 255);
}

TEST(child_killed_by_a_signal) {
    CHECK_EQ(child([] { raise(SIGKILL); return 0; }), 128 + SIGKILL);
    CHECK_EQ(child([] { raise(SIGTERM); return 0; }), 128 + SIGTERM);
    CHECK(no_children_left());
}

TEST(the_child_has_its_own_memory) {
    shared_number = 1;
    CHECK_EQ(child([] { shared_number = 42; return shared_number; }), 42);
    CHECK_EQ(shared_number, 1);              // the parent's copy is untouched
}

TEST(the_child_runs_in_another_process) {
    const int parent = static_cast<int>(getpid()) % 251;
    const int seen = child([] { return static_cast<int>(getppid()) % 251; });
    CHECK_EQ(seen, parent);                  // the child's parent is us
    CHECK_EQ(child([] { return getpid() == test_pid ? 1 : 0; }), 0);
}

TEST(capture_a_line) {
    CHECK_EQ(cap([] { say("coo\n"); }), std::string("coo\n"));
    CHECK(no_children_left());
}

TEST(capture_nothing) {
    CHECK_EQ(cap([] {}), std::string(""));
}

TEST(capture_several_writes) {
    CHECK_EQ(cap([] { say("one "); say("two "); say("three"); }), std::string("one two three"));
}

TEST(capture_printf_and_cout) {
    std::cout << "";                          // (the test runner's own output may be sitting in a buffer)
    CHECK_EQ(cap([] { std::printf("x=%d\n", 5); }), std::string("x=5\n"));
    CHECK_EQ(cap([] { std::cout << "pi is " << 3 << '\n'; }), std::string("pi is 3\n"));
}

TEST(capture_only_what_the_child_wrote) {
    // Text still buffered in the parent when it forks must not leak into the child's output.
    std::printf("%s", "");
    std::fputs("(parent talking) ", stdout);
    const std::string got = cap([] { say("child"); });
    std::fputs("\n", stdout);
    CHECK_EQ(got, std::string("child"));
}

TEST(capture_a_megabyte) {
    // Far more than a pipe holds: the parent has to read while the child writes.
    const std::string got = cap([] {
        const std::string line(1023, 'x');
        for (int i = 0; i < 1024; ++i) { say(line.c_str()); say("\n"); }
    });
    CHECK_EQ(got.size(), std::size_t{1024} * 1024);
    std::size_t newlines = 0, xs = 0;
    for (char ch : got) { newlines += ch == '\n'; xs += ch == 'x'; }
    CHECK_EQ(newlines, std::size_t{1024});
    CHECK_EQ(xs, std::size_t{1023} * 1024);
    CHECK(no_children_left());
}

TEST(capture_does_not_leak_file_descriptors) {
    int wrong = 0;
    for (int i = 0; i < 1500; ++i)
        if (cap([] { say("."); }) != ".") ++wrong;
    CHECK_EQ(wrong, 0);
    // The lowest free descriptor is still a small number if nothing was left open.
    const int probe = dup(STDIN_FILENO);
    close(probe);
    CHECK(probe >= 0 && probe < 20);
    CHECK(no_children_left());
}

TEST(run_echo) {
    const Result r = prog({"echo", "hello", "world"});
    CHECK_EQ(r.status, 0);
    CHECK_EQ(r.out, std::string("hello world\n"));
    CHECK(no_children_left());
}

TEST(arguments_are_not_split_by_a_shell) {
    const Result r = prog({"echo", "two  spaces", "$HOME", "*"});
    CHECK_EQ(r.out, std::string("two  spaces $HOME *\n"));
}

TEST(run_reports_the_exit_code) {
    const Result r = prog({"sh", "-c", "printf abc; exit 3"});
    CHECK_EQ(r.status, 3);
    CHECK_EQ(r.out, std::string("abc"));
    CHECK_EQ(prog({"true"}).status, 0);
    CHECK_EQ(prog({"false"}).status, 1);
}

TEST(run_reports_death_by_signal) {
    const Result r = prog({"sh", "-c", "kill -9 $$"});
    CHECK_EQ(r.status, 128 + SIGKILL);
}

TEST(a_program_that_does_not_exist) {
    const Result r = prog({"no-such-program-anywhere-4f1c"});
    CHECK_EQ(r.status, 127);
    CHECK_EQ(r.out, std::string(""));
    CHECK(no_children_left());
}

TEST(run_a_program_with_a_lot_of_output) {
    const Result r = prog({"sh", "-c", "head -c 300000 /dev/zero | tr '\\0' 'z'"});
    CHECK_EQ(r.status, 0);
    CHECK_EQ(r.out.size(), std::size_t{300000});
    CHECK(r.out.find_first_not_of('z') == std::string::npos);
}
