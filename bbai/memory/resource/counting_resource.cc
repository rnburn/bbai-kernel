#include "bbai/memory/resource/counting_resource.h"

namespace bbai::memr {
//--------------------------------------------------------------------------------------------------
// constructor
//--------------------------------------------------------------------------------------------------
counting_resource::counting_resource(
    std::pmr::memory_resource* upstream) noexcept
    : upstream_{upstream} {}

//--------------------------------------------------------------------------------------------------
// do_allocate
//--------------------------------------------------------------------------------------------------
void* counting_resource::do_allocate(size_t num_bytes,
                                     size_t alignment) noexcept {
  count_ += num_bytes;
  return upstream_->allocate(num_bytes, alignment);
}

//--------------------------------------------------------------------------------------------------
// do_deallocate
//--------------------------------------------------------------------------------------------------
void counting_resource::do_deallocate(void* ptr, size_t num_bytes,
                                      size_t alignment) noexcept {
  count_ -= num_bytes;
  return upstream_->deallocate(ptr, num_bytes, alignment);
  ;
}
}  // namespace bbai::memr
