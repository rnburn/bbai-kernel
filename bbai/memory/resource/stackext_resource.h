#pragma once

#include <memory_resource>

namespace bbai::memr {
//--------------------------------------------------------------------------------------------------
// stackext_resource
//--------------------------------------------------------------------------------------------------
class stackext_resource final : public std::pmr::memory_resource {
 public:
  explicit stackext_resource(std::pmr::memory_resource* upstream =
                                 std::pmr::get_default_resource()) noexcept;

  ~stackext_resource() noexcept override;

  void release() noexcept;
 private:
  std::pmr::monotonic_buffer_resource upstream_;
  size_t size_{0};

  // std::pmr::memory_resource
  void* do_allocate(size_t num_bytes, size_t alignment) noexcept override;

  void do_deallocate(void* /*ptr*/, size_t /*num_bytes*/,
                     size_t /*alignment*/) noexcept override {}

  bool do_is_equal(
      const std::pmr::memory_resource& other) const noexcept override {
    return this == &other;
  }
};
} // namespace bbai::memr
