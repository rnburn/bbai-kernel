#include "bbai/memory/resource/stackext_resource.h"

#include <memory>

#include "bbai/memory/resource/stack_extension.h"

namespace bbai::memr {
//--------------------------------------------------------------------------------------------------
// constructor
//--------------------------------------------------------------------------------------------------
stackext_resource::stackext_resource(
    std::pmr::memory_resource* upstream) noexcept
    : upstream_{upstream} {}

//--------------------------------------------------------------------------------------------------
// destructor
//--------------------------------------------------------------------------------------------------
stackext_resource::~stackext_resource() noexcept {
  stack_extension::deallocate(size_);
}

//--------------------------------------------------------------------------------------------------
// release
//--------------------------------------------------------------------------------------------------
void stackext_resource::release() noexcept {
  stack_extension::deallocate(size_);
  size_ = 0;
  upstream_.release();
}

//--------------------------------------------------------------------------------------------------
// do_allocate
//--------------------------------------------------------------------------------------------------
void* stackext_resource::do_allocate(size_t num_bytes,
                                     size_t alignment) noexcept {
  auto free_space = stack_extension::capacity() - stack_extension::size();
  auto free_space_p = free_space;
  auto ptr = stack_extension::top();
  if (std::align(alignment, num_bytes, ptr, free_space_p) == nullptr) {
    return upstream_.allocate(num_bytes, alignment);
  }
  free_space_p -= num_bytes;
  auto num_bytes_p = free_space - free_space_p;
  size_ += num_bytes_p;
  stack_extension::allocate(num_bytes_p);
  return ptr;
}
} // bbai::memr
