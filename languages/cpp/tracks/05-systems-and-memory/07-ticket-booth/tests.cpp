#include <atomic>
#include <chrono>
#include <latch>
#include <mutex>
#include <thread>
#include <vector>

#include "mini_test.hpp"

#ifndef SOLUTION
#define SOLUTION "solution.cpp"
#endif
#include SOLUTION

using namespace std::chrono_literals;

// Starts `threads` threads that all begin `body(t)` at (nearly) the same instant, and waits for them.
template <class Body>
static void stampede(int threads, Body body) {
    std::latch gate(1);
    std::vector<std::jthread> crowd;
    for (int t = 0; t < threads; ++t)
        crowd.emplace_back([&gate, &body, t] { gate.wait(); body(t); });
    gate.count_down();
}

TEST(booth_sells_until_empty) {
    TicketBooth booth(2);
    CHECK_EQ(booth.remaining(), 2);
    CHECK(booth.try_buy());
    CHECK_EQ(booth.remaining(), 1);
    CHECK(booth.try_buy());
    CHECK(!booth.try_buy());
    CHECK(!booth.try_buy());
    CHECK_EQ(booth.remaining(), 0);
}

TEST(booth_with_nothing_to_sell) {
    TicketBooth booth(0);
    CHECK(!booth.try_buy());
    CHECK_EQ(booth.remaining(), 0);
}

TEST(booth_never_oversells) {
    const int tickets = 300000;
    TicketBooth booth(tickets);
    std::atomic<int> sold{0};
    stampede(8, [&](int) {
        int mine = 0;
        for (int i = 0; i < 100000; ++i)
            if (booth.try_buy()) ++mine;
        sold += mine;
    });
    CHECK_EQ(sold.load(), tickets);
    CHECK_EQ(booth.remaining(), 0);
}

TEST(booth_with_more_tickets_than_buyers) {
    TicketBooth booth(1000000);
    std::atomic<int> sold{0};
    stampede(8, [&](int) {
        int mine = 0;
        for (int i = 0; i < 50000; ++i)
            if (booth.try_buy()) ++mine;
        sold += mine;
    });
    CHECK_EQ(sold.load(), 400000);
    CHECK_EQ(booth.remaining(), 600000);
}

TEST(the_last_ticket_is_sold_exactly_once) {
    int wrong = 0;
    for (int round = 0; round < 300; ++round) {
        TicketBooth booth(1);
        std::atomic<int> sold{0};
        stampede(4, [&](int) { if (booth.try_buy()) ++sold; });
        if (sold != 1 || booth.remaining() != 0) ++wrong;
    }
    CHECK_EQ(wrong, 0);
}

TEST(remaining_is_never_seen_below_zero) {
    long long negatives = 0;
    for (int round = 0; round < 20; ++round) {
        TicketBooth booth(50);
        std::atomic<bool> done{false};
        std::jthread watcher([&] {
            while (!done)
                if (booth.remaining() < 0) ++negatives;      // only this thread touches `negatives`
        });
        stampede(8, [&](int) { for (int i = 0; i < 20000; ++i) booth.try_buy(); });
        done = true;
    }
    CHECK_EQ(negatives, 0LL);
}

TEST(lazy_does_nothing_until_asked) {
    int calls = 0;
    Lazy lazy([&] { ++calls; return 7; });
    CHECK_EQ(calls, 0);
    CHECK_EQ(lazy.get(), 7);
    CHECK_EQ(calls, 1);
    CHECK_EQ(lazy.get(), 7);
    CHECK_EQ(lazy.get(), 7);
    CHECK_EQ(calls, 1);
}

TEST(lazy_keeps_the_first_value) {
    int n = 10;
    Lazy lazy([&] { return n++; });
    CHECK_EQ(lazy.get(), 10);
    CHECK_EQ(lazy.get(), 10);
    CHECK_EQ(n, 11);
}

TEST(lazy_runs_the_factory_once_under_a_stampede) {
    int wrong = 0;
    for (int round = 0; round < 25; ++round) {
        std::atomic<int> calls{0};
        Lazy lazy([&] {
            std::this_thread::sleep_for(5ms);               // a slow factory: plenty of time to collide
            return 100 + calls.fetch_add(1);                // a second call would return 101
        });
        std::atomic<int> not_100{0};
        stampede(8, [&](int) { if (lazy.get() != 100) ++not_100; });
        if (calls != 1 || not_100 != 0) ++wrong;
    }
    CHECK_EQ(wrong, 0);
}

TEST(spinlock_try_lock) {
    SpinLock s;
    CHECK(s.try_lock());
    CHECK(!s.try_lock());       // already held
    s.unlock();
    CHECK(s.try_lock());
    s.unlock();
    s.lock();
    CHECK(!s.try_lock());
    s.unlock();
}

TEST(spinlock_blocks_other_threads) {
    SpinLock s;
    std::atomic<bool> entered{false};
    bool early = false;
    s.lock();
    {
        std::jthread other([&] { std::lock_guard lock(s); entered = true; });
        std::this_thread::sleep_for(50ms);
        early = entered;
        s.unlock();
    }
    CHECK(!early);
    CHECK(entered.load());
}

TEST(spinlock_protects_a_plain_counter) {
    SpinLock s;
    volatile long long counter = 0;      // volatile only to stop the compiler merging the increments
    stampede(8, [&](int) {
        for (int i = 0; i < 100000; ++i) {
            std::lock_guard lock(s);
            counter = counter + 1;
        }
    });
    CHECK_EQ(static_cast<long long>(counter), 800000LL);
}
