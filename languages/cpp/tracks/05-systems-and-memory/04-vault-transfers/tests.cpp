#include <atomic>
#include <thread>
#include <vector>

#include "mini_test.hpp"

#ifndef SOLUTION
#define SOLUTION "solution.cpp"
#endif
#include SOLUTION

TEST(opening_balances) {
    Bank bank({100, 50, 0});
    CHECK_EQ(bank.balance(0), 100LL);
    CHECK_EQ(bank.balance(1), 50LL);
    CHECK_EQ(bank.balance(2), 0LL);
    CHECK_EQ(bank.total(), 150LL);
}

TEST(a_simple_transfer) {
    Bank bank({100, 50});
    CHECK(bank.transfer(0, 1, 30));
    CHECK_EQ(bank.balance(0), 70LL);
    CHECK_EQ(bank.balance(1), 80LL);
    CHECK_EQ(bank.total(), 150LL);
}

TEST(insufficient_funds_change_nothing) {
    Bank bank({100, 50});
    CHECK(!bank.transfer(0, 1, 101));
    CHECK_EQ(bank.balance(0), 100LL);
    CHECK_EQ(bank.balance(1), 50LL);
    CHECK(bank.transfer(0, 1, 100));      // exactly everything is allowed
    CHECK_EQ(bank.balance(0), 0LL);
    CHECK(bank.transfer(0, 1, 0));        // moving nothing always works
}

TEST(transfer_to_the_same_account) {
    Bank bank({100, 50});
    CHECK(bank.transfer(1, 1, 50));
    CHECK(!bank.transfer(1, 1, 51));
    CHECK_EQ(bank.balance(1), 50LL);
    CHECK_EQ(bank.total(), 150LL);
}

TEST(opposite_transfers_do_not_deadlock) {
    Bank bank({1000000, 1000000});
    {
        std::jthread a([&] { for (int i = 0; i < 300000; ++i) bank.transfer(0, 1, 1); });
        std::jthread b([&] { for (int i = 0; i < 300000; ++i) bank.transfer(1, 0, 1); });
    }
    CHECK_EQ(bank.balance(0), 1000000LL);
    CHECK_EQ(bank.balance(1), 1000000LL);
}

TEST(a_ring_of_tellers_does_not_deadlock) {
    const std::size_t n = 5;
    Bank bank(std::vector<long long>(n, 1000000));
    {
        std::vector<std::jthread> tellers;
        for (std::size_t t = 0; t < n; ++t)
            tellers.emplace_back([&bank, t, n] {
                for (int i = 0; i < 100000; ++i) bank.transfer(t, (t + 1) % n, 1);
            });
    }
    for (std::size_t i = 0; i < n; ++i) CHECK_EQ(bank.balance(i), 1000000LL);
}

TEST(nobody_goes_overdrawn) {
    // Eight threads all try to drain the same small account: exactly 1000 units can leave it.
    Bank bank({1000, 0});
    std::atomic<int> succeeded{0};
    {
        std::vector<std::jthread> tellers;
        for (int t = 0; t < 8; ++t)
            tellers.emplace_back([&] {
                for (int i = 0; i < 50000; ++i)
                    if (bank.transfer(0, 1, 1)) ++succeeded;
            });
    }
    CHECK_EQ(succeeded.load(), 1000);
    CHECK_EQ(bank.balance(0), 0LL);
    CHECK_EQ(bank.balance(1), 1000LL);
}

TEST(total_is_a_consistent_snapshot_during_a_storm) {
    const std::size_t n = 16;
    const long long opening = 500;
    Bank bank(std::vector<long long>(n, opening));
    std::atomic<bool> done{false};
    std::atomic<long long> bad_totals{0};
    std::atomic<long long> audits{0};
    {
        std::jthread auditor([&] {
            while (!done) {
                if (bank.total() != static_cast<long long>(n) * opening) ++bad_totals;
                ++audits;
            }
        });
        {
            std::vector<std::jthread> tellers;
            for (unsigned t = 0; t < 8; ++t)
                tellers.emplace_back([&bank, t, n] {
                    unsigned state = 12345u + t * 7919u;                 // tiny private random generator
                    auto next = [&state] { state = state * 1664525u + 1013904223u; return state >> 8; };
                    for (int i = 0; i < 100000; ++i) {
                        const std::size_t from = next() % n;
                        const std::size_t to = next() % n;
                        bank.transfer(from, to, static_cast<long long>(next() % 300));
                    }
                });
        }
        done = true;
    }
    CHECK(audits.load() > 0);
    CHECK_EQ(bad_totals.load(), 0LL);
    CHECK_EQ(bank.total(), static_cast<long long>(n) * opening);
    for (std::size_t i = 0; i < n; ++i) CHECK(bank.balance(i) >= 0);
}
