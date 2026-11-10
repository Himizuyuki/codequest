#include <atomic>
#include <functional>
#include <mutex>
#include <utility>

class TicketBooth {
public:
    explicit TicketBooth(int tickets) {
        // TODO: see problem.md
        (void)tickets;
    }

    bool try_buy() {
        // TODO: see problem.md
        return false;
    }

    int remaining() const {
        // TODO: see problem.md
        return -1;
    }

private:
    // TODO: add your data member
};

class Lazy {
public:
    explicit Lazy(std::function<int()> make) {
        // TODO: see problem.md
        (void)make;
    }

    int get() {
        // TODO: see problem.md
        return -1;
    }

private:
    // TODO: add your data members
};

class SpinLock {
public:
    void lock() {
        // TODO: see problem.md
    }

    bool try_lock() {
        // TODO: see problem.md
        return false;
    }

    void unlock() {
        // TODO: see problem.md
    }

private:
    // TODO: add your data member
};
