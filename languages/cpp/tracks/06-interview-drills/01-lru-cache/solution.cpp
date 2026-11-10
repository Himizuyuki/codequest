#include <cstddef>
#include <list>
#include <optional>
#include <unordered_map>
#include <utility>

class LRUCache {
public:
    explicit LRUCache(std::size_t capacity) {
        // TODO: see problem.md
        (void)capacity;
    }

    std::optional<int> get(int key) {
        // TODO: see problem.md
        (void)key;
        return std::nullopt;
    }

    void put(int key, int value) {
        // TODO: see problem.md
        (void)key;
        (void)value;
    }

    std::size_t size() const {
        // TODO: see problem.md
        return 0;
    }

private:
    // TODO: add your data members
};
