#include <cstddef>
#include <memory>
#include <stdexcept>
#include <utility>

class Stack {
public:
    void push(int value) {
        // TODO: see problem.md
        (void)value;
    }

    int pop() {
        // TODO: see problem.md
        throw std::out_of_range("Stack::pop is not implemented yet");
    }

    int top() const {
        // TODO: see problem.md
        throw std::out_of_range("Stack::top is not implemented yet");
    }

    std::size_t size() const { return size_; }
    bool empty() const { return size_ == 0; }

    ~Stack() {
        // TODO: see "The catch" in problem.md
    }

private:
    struct Node {
        int value;
        std::unique_ptr<Node> next;
    };
    std::unique_ptr<Node> head_;
    std::size_t size_ = 0;
};
