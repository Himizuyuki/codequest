#include <algorithm>
#include <cstddef>
#include <stdexcept>
#include <utility>

class Buffer {
public:
    explicit Buffer(std::size_t size) {
        // TODO: allocate `size` zero-initialised ints
        (void)size;
    }

    Buffer(const Buffer& other) {
        // TODO: deep copy
        (void)other;
    }

    Buffer(Buffer&& other) noexcept {
        // TODO: steal other's memory and leave it empty
        (void)other;
    }

    Buffer& operator=(const Buffer& other) {
        // TODO
        (void)other;
        return *this;
    }

    Buffer& operator=(Buffer&& other) noexcept {
        // TODO
        (void)other;
        return *this;
    }

    ~Buffer() {
        // TODO: release the memory
    }

    std::size_t size() const { return size_; }
    const int* data() const { return data_; }

    int& at(std::size_t i) {
        // TODO: return the element, or throw std::out_of_range if i >= size()
        (void)i;
        throw std::out_of_range("Buffer::at is not implemented yet");
    }

    const int& at(std::size_t i) const {
        // TODO
        (void)i;
        throw std::out_of_range("Buffer::at is not implemented yet");
    }

private:
    std::size_t size_ = 0;
    int* data_ = nullptr;
};
