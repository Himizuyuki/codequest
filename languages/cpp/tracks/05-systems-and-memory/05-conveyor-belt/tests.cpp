#include <atomic>
#include <chrono>
#include <optional>
#include <thread>
#include <vector>

#include "mini_test.hpp"

#ifndef SOLUTION
#define SOLUTION "solution.cpp"
#endif
#include SOLUTION

using O = std::optional<int>;
static const O none = std::nullopt;
using namespace std::chrono_literals;

TEST(first_in_first_out) {
    BoundedQueue q(3);
    CHECK_EQ(q.size(), std::size_t{0});
    CHECK(q.push(1));
    CHECK(q.push(2));
    CHECK(q.push(3));
    CHECK_EQ(q.size(), std::size_t{3});
    CHECK_EQ(q.pop(), O{1});
    CHECK(q.push(4));
    CHECK_EQ(q.pop(), O{2});
    CHECK_EQ(q.pop(), O{3});
    CHECK_EQ(q.pop(), O{4});
    CHECK_EQ(q.size(), std::size_t{0});
}

TEST(close_keeps_what_is_inside_and_refuses_more) {
    BoundedQueue q(4);
    CHECK(q.push(7));
    CHECK(q.push(8));
    q.close();
    q.close();                     // twice is harmless
    CHECK(!q.push(9));
    CHECK_EQ(q.size(), std::size_t{2});
    CHECK_EQ(q.pop(), O{7});
    CHECK_EQ(q.pop(), O{8});
    CHECK_EQ(q.pop(), none);
    CHECK_EQ(q.pop(), none);
}

TEST(pop_waits_for_a_value) {
    BoundedQueue q(1);
    std::atomic<bool> returned{false};
    O got;
    bool early = false;
    {
        std::jthread loader([&] { got = q.pop(); returned = true; });
        std::this_thread::sleep_for(100ms);
        early = returned;                    // must still be blocked: the queue is empty
        q.push(42);
    }
    CHECK(!early);
    CHECK_EQ(got, O{42});
}

TEST(push_waits_for_room) {
    BoundedQueue q(2);
    CHECK(q.push(1));
    CHECK(q.push(2));
    std::atomic<bool> returned{false};
    bool pushed = false;
    bool early = false;
    O first;
    {
        std::jthread packer([&] { pushed = q.push(3); returned = true; });
        std::this_thread::sleep_for(100ms);
        early = returned;                    // must still be blocked: the queue is full
        first = q.pop();
    }
    CHECK(!early);
    CHECK(pushed);
    CHECK_EQ(first, O{1});
    CHECK_EQ(q.size(), std::size_t{2});
    CHECK_EQ(q.pop(), O{2});
    CHECK_EQ(q.pop(), O{3});
}

TEST(close_wakes_every_waiting_loader) {
    BoundedQueue q(2);
    std::atomic<int> got_nothing{0};
    {
        std::vector<std::jthread> loaders;
        for (int i = 0; i < 4; ++i)
            loaders.emplace_back([&] { if (!q.pop()) ++got_nothing; });
        std::this_thread::sleep_for(100ms);
        q.close();
    }                                        // hangs here if a loader was not woken
    CHECK_EQ(got_nothing.load(), 4);
}

TEST(close_wakes_every_waiting_packer) {
    BoundedQueue q(1);
    CHECK(q.push(1));
    std::atomic<int> refused{0};
    {
        std::vector<std::jthread> packers;
        for (int i = 0; i < 4; ++i)
            packers.emplace_back([&] { if (!q.push(99)) ++refused; });
        std::this_thread::sleep_for(100ms);
        q.close();
    }
    CHECK_EQ(refused.load(), 4);
    CHECK_EQ(q.pop(), O{1});
    CHECK_EQ(q.pop(), none);
}

TEST(each_packers_parcels_stay_in_order) {
    const int packers = 3, per_packer = 20000;
    BoundedQueue q(8);
    std::vector<int> last(packers, -1);
    long long out_of_order = 0, received = 0;
    {
        std::jthread loader([&] {
            while (auto v = q.pop()) {
                const int who = *v / 1000000, seq = *v % 1000000;
                if (who < 0 || who >= packers || seq != last[who] + 1) ++out_of_order;
                else last[who] = seq;
                ++received;
            }
        });
        {
            std::vector<std::jthread> workers;
            for (int p = 0; p < packers; ++p)
                workers.emplace_back([&q, p] {
                    for (int i = 0; i < per_packer; ++i) q.push(p * 1000000 + i);
                });
        }
        q.close();
    }
    CHECK_EQ(received, static_cast<long long>(packers) * per_packer);
    CHECK_EQ(out_of_order, 0LL);
}

TEST(many_packers_many_loaders_nothing_lost_nothing_doubled) {
    const int packers = 4, loaders = 4, per_packer = 50000;
    const std::size_t capacity = 16;
    BoundedQueue q(capacity);
    std::atomic<long long> sum{0}, count{0}, over_capacity{0};
    {
        std::vector<std::jthread> consumers;
        for (int l = 0; l < loaders; ++l)
            consumers.emplace_back([&] {
                long long my_sum = 0, my_count = 0;
                while (auto v = q.pop()) {
                    my_sum += *v;
                    ++my_count;
                    if (q.size() > capacity) ++over_capacity;
                }
                sum += my_sum;
                count += my_count;
            });
        {
            std::vector<std::jthread> producers;
            for (int p = 0; p < packers; ++p)
                producers.emplace_back([&q, p] {
                    for (int i = 0; i < per_packer; ++i) q.push(p * per_packer + i);
                });
        }
        q.close();
    }
    const long long n = static_cast<long long>(packers) * per_packer;
    CHECK_EQ(count.load(), n);
    CHECK_EQ(sum.load(), n * (n - 1) / 2);
    CHECK_EQ(over_capacity.load(), 0LL);
    CHECK_EQ(q.size(), std::size_t{0});
}

TEST(a_one_slot_belt_with_a_crowd_on_both_sides) {
    // With a single slot, packers and loaders are asleep at the same time all the time:
    // waking "one of them" is not good enough if it can be the wrong kind.
    const int crowd = 6, per_packer = 8000;
    BoundedQueue q(1);
    std::atomic<long long> count{0};
    {
        std::vector<std::jthread> consumers;
        for (int l = 0; l < crowd; ++l)
            consumers.emplace_back([&] {
                long long mine = 0;
                while (q.pop()) ++mine;
                count += mine;
            });
        {
            std::vector<std::jthread> producers;
            for (int p = 0; p < crowd; ++p)
                producers.emplace_back([&q] {
                    for (int i = 0; i < per_packer; ++i) q.push(i);
                });
        }
        q.close();
    }
    CHECK_EQ(count.load(), static_cast<long long>(crowd) * per_packer);
}
