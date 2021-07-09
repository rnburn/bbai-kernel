#pragma once

#include <cstddef>

namespace bbai::memr {
//--------------------------------------------------------------------------------------------------
// stack_extension
//--------------------------------------------------------------------------------------------------
struct stack_extension {
  static size_t capacity() noexcept;

  static size_t size() noexcept;

  static void* top() noexcept;

  static void* allocate(size_t num_bytes) noexcept;

  static void deallocate(size_t num_bytes) noexcept;
};
} // namespace bbai::memr
