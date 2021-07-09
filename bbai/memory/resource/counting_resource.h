#pragma once

#include <cstddef>
#include <memory_resource>

namespace bbai::memr {
//--------------------------------------------------------------------------------------------------
// counting_resource
//--------------------------------------------------------------------------------------------------
class counting_resource final : public std::pmr::memory_resource {
 public:
  explicit counting_resource(std::pmr::memory_resource* upstream =
                                 std::pmr::get_default_resource()) noexcept;

  size_t count() const noexcept { return count_; }

 private:
  std::pmr::memory_resource* upstream_;
  size_t count_{0};

  // std::pmr::memory_resource
  void* do_allocate(size_t num_bytes, size_t alignment) noexcept override;

  void do_deallocate(void* ptr, size_t num_bytes,
                     size_t alignment) noexcept override;

  bool do_is_equal(
      const std::pmr::memory_resource& other) const noexcept override {
    return upstream_->is_equal(other);
  }
};
}  // namespace bbai::memr
