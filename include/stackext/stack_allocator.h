#pragma once

#include <cassert>
#include <memory>

namespace stackext {
class stack_allocator {
 public:
  explicit stack_allocator(size_t max_size)
      : data_{new char[max_size]}, max_size_{max_size} {}

  size_t max_size() const noexcept { return max_size_; }

  size_t size() const noexcept { return size_; }

  void* top() noexcept { return static_cast<void*>(data_.get() + size_); }

  void* allocate(size_t num_bytes) noexcept {
    void* result = top();
    size_ += num_bytes;
    assert(size_ <= max_size_);
    return result;
  }

  void deallocate(size_t num_bytes) noexcept {
    assert(size_ >= num_bytes);
    size_ -= num_bytes;
  }

 private:
  std::unique_ptr<char[]> data_;
  size_t max_size_;
  size_t size_{0};
};
}  // namespace stackext
