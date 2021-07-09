#pragma once

#include <concepts>
#include <memory>
#include <memory_resource>
#include <utility>

namespace bbai::memmg {
//--------------------------------------------------------------------------------------------------
// pointer_operator_function_v
//--------------------------------------------------------------------------------------------------
template <std::move_constructible Derived>
const auto pointer_operator_function_v =
    [](const void* other, std::pmr::polymorphic_allocator<> alloc,
       bool construct) noexcept -> void* {
  // We de-constify other so that we can move from it before we destroy it.
  auto other_p = const_cast<Derived*>(static_cast<const Derived*>(other));
  if (construct) {
    return static_cast<void*>(alloc.new_object<Derived>(std::move(*other_p)));
  } else {
    std::allocator_traits<std::pmr::polymorphic_allocator<>>::destroy(alloc,
                                                                      other_p);
    alloc.deallocate_object(other_p);
    return nullptr;
  }
};
} // namespace bbai::memmg
