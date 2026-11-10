#include <cstddef>
#include <mutex>
#include <numeric>
#include <vector>

class Bank {
public:
    explicit Bank(std::vector<long long> balances) {
        // TODO: see problem.md
        (void)balances;
    }

    bool transfer(std::size_t from, std::size_t to, long long amount) {
        // TODO: see problem.md
        (void)from; (void)to; (void)amount;
        return false;
    }

    long long balance(std::size_t account) const {
        // TODO: see problem.md
        (void)account;
        return -1;
    }

    long long total() const {
        // TODO: see problem.md
        return -1;
    }

private:
    // TODO: add your data members (a const method that locks needs a `mutable` mutex)
};
