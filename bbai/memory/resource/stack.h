#pragma once

#include <array>
#include <cassert>
#include <cstddef>

namespace bbai::memr {
//--------------------------------------------------------------------------------------------------
// stack
//--------------------------------------------------------------------------------------------------
template <size_t N>
class stack {
 public:
  size_t capacity() const noexcept { return N; }

  size_t size() const noexcept { return size_; }

  void* top() noexcept { return static_cast<void*>(data_.data() + size_); }

  void* allocate(size_t num_bytes) noexcept {
    void* ptr = this->top();
    size_ += num_bytes;
    assert(size_ <= N);
    return ptr;
  }

  void deallocate(size_t num_bytes) noexcept {
    assert(size_ >= num_bytes);
    size_ -= num_bytes;
  }
 private:
   std::array<std::byte, N> data_{};
   size_t size_{0};
};
} // namespace bbai::memr
