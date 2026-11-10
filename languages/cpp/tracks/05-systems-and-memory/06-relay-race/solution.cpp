#include <atomic>
#include <condition_variable>
#include <functional>
#include <mutex>

class Relay {
public:
    explicit Relay(int runners) {
        // TODO: see problem.md
        (void)runners;
    }

    void run(int id, const std::function<void()>& leg) {
        // TODO: wait for runner `id`'s turn, call leg(), pass the baton on
        (void)id;
        (void)leg;
    }

private:
    // TODO: add your data members
};
