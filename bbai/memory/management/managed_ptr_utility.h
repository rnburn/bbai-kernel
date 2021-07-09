#pragma once

#include <concepts>
#include <memory_resource>

#include "bbai/memory/management/managed_ptr.h"

namespace bbai::memmg {
//--------------------------------------------------------------------------------------------------
// allocate_managed
//--------------------------------------------------------------------------------------------------
template <std::move_constructible T, class... Args>
managed_ptr<T> allocate_managed(std::pmr::polymorphic_allocator<> alloc, Args&&... args) {
  return managed_ptr<T>{alloc.new_object<T>(std::forward<Args>(args)...), alloc};
}
} // namespace bbai::memmg
