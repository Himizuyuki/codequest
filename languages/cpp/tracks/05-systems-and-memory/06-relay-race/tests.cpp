#include <atomic>
#include <chrono>
#include <thread>
#include <vector>

#include "mini_test.hpp"

#ifndef SOLUTION
#define SOLUTION "solution.cpp"
#endif
#include SOLUTION

using namespace std::chrono_literals;

// Runs `runners` threads for `laps` laps each and returns the order in which the legs executed.
// Slots are handed out with an atomic index, so even a broken Relay cannot corrupt the log.
static std::vector<int> race(int runners, int laps, bool start_in_reverse = false) {
    Relay relay(runners);
    std::vector<int> log(static_cast<std::size_t>(runners) * laps, -1);
    std::atomic<std::size_t> next{0};
    {
        std::vector<std::jthread> threads;
        for (int k = 0; k < runners; ++k) {
            const int id = start_in_reverse ? runners - 1 - k : k;
            threads.emplace_back([&, id] {
                for (int lap = 0; lap < laps; ++lap)
                    relay.run(id, [&] {
                        const std::size_t slot = next.fetch_add(1);
                        if (slot < log.size()) log[slot] = id;
                    });
            });
            if (start_in_reverse) std::this_thread::sleep_for(20ms);   // give the "wrong" runner a head start
        }
    }
    return log;
}

static std::vector<int> round_robin(int runners, int laps) {
    std::vector<int> expected;
    for (int lap = 0; lap < laps; ++lap)
        for (int id = 0; id < runners; ++id) expected.push_back(id);
    return expected;
}

TEST(a_single_runner_never_waits) {
    Relay relay(1);
    int legs = 0;
    for (int i = 0; i < 5; ++i) relay.run(0, [&] { ++legs; });
    CHECK_EQ(legs, 5);
}

TEST(the_leg_runs_on_the_calling_thread) {
    Relay relay(1);
    std::thread::id where;
    relay.run(0, [&] { where = std::this_thread::get_id(); });
    CHECK(where == std::this_thread::get_id());
}

TEST(two_runners_alternate) {
    CHECK_EQ(race(2, 5), round_robin(2, 5));
}

TEST(three_runners_two_laps) {
    CHECK_EQ(race(3, 2), round_robin(3, 2));
}

TEST(runner_zero_goes_first_even_when_it_starts_last) {
    CHECK_EQ(race(4, 3, true), round_robin(4, 3));
}

TEST(a_waiting_runner_really_waits) {
    Relay relay(2);
    std::atomic<bool> ran{false};
    bool early = false;
    {
        std::jthread second([&] { relay.run(1, [&] { ran = true; }); });
        std::this_thread::sleep_for(100ms);
        early = ran;                         // runner 1 must still be blocked
        relay.run(0, [] {});
    }
    CHECK(!early);
    CHECK(ran.load());
}

TEST(legs_never_overlap) {
    const int runners = 6, laps = 300;
    Relay relay(runners);
    std::atomic<int> inside{0}, overlaps{0}, legs{0};
    {
        std::vector<std::jthread> threads;
        for (int id = 0; id < runners; ++id)
            threads.emplace_back([&, id] {
                for (int lap = 0; lap < laps; ++lap)
                    relay.run(id, [&] {
                        if (inside.fetch_add(1) != 0) ++overlaps;
                        std::this_thread::yield();
                        inside.fetch_sub(1);
                        ++legs;
                    });
            });
    }
    CHECK_EQ(legs.load(), runners * laps);
    CHECK_EQ(overlaps.load(), 0);
}

TEST(a_long_race_with_many_runners) {
    CHECK_EQ(race(8, 2000), round_robin(8, 2000));
    CHECK_EQ(race(3, 10000), round_robin(3, 10000));
}
