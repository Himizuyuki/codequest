#include <condition_variable>
#include <cstddef>
#include <deque>
#include <mutex>
#include <optional>

class BoundedQueue {
public:
    explicit BoundedQueue(std::size_t capacity) {
        // TODO: see problem.md
        (void)capacity;
    }

    bool push(int value) {
        // TODO: see problem.md
        (void)value;
        return false;
    }

    std::optional<int> pop() {
        // TODO: see problem.md
        return std::nullopt;
    }

    void close() {
        // TODO: see problem.md
    }

    std::size_t size() const {
        // TODO: see problem.md
        return 0;
    }

private:
    // TODO: add your data members
};
