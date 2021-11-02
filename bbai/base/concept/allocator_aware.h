#pragma once

#include <memory_resource>
#include <type_traits>

#include "bbai/base/type/uncvref.h"

namespace bbai::basc {
//------------------------------------------------------------------------------
// allocator_aware
//------------------------------------------------------------------------------
template <class T>
concept allocator_aware = requires(std::pmr::polymorphic_allocator<> alloc, T other) {
  typename T::allocator_type;
  T{};
  T{alloc};
  T{std::move(other), alloc};
};
} // namespace bbai::basc
