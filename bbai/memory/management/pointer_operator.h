#pragma once

#include <concepts>
#include <memory_resource>
#include <type_traits>

#include "bbai/memory/management/pointer_operator_function.h"

namespace bbai::memmg {
//--------------------------------------------------------------------------------------------------
// pointer_operator
//--------------------------------------------------------------------------------------------------
template <class T>
class pointer_operator {
 public:
  using operator_function_pointer =
      void* (*)(const void*, std::pmr::polymorphic_allocator<>, bool) noexcept;

  pointer_operator() noexcept = default;

  template <class U>
    requires std::convertible_to<U*, T*>
  pointer_operator(const U* ptr, pointer_operator<U> other) noexcept
      : operator_function_{other.operator_function()},
        derived_ptr_{other.get_derived_pointer(ptr)} {}

  template <std::move_constructible U>
    requires std::convertible_to<U*, T*>
  explicit pointer_operator(const U* derived_ptr) noexcept
        : operator_function_{pointer_operator_function_v<U>},
          derived_ptr_{static_cast<const void*>(derived_ptr)} {}

  T* allocate_from(const T* ptr,
                   std::pmr::polymorphic_allocator<> alloc) noexcept {
    auto derived_p = (*operator_function_)(derived_ptr_, alloc, true);
    auto offset = reinterpret_cast<const char*>(ptr) -
                  reinterpret_cast<const char*>(derived_ptr_);
    derived_ptr_ = derived_p;
    return reinterpret_cast<T*>(reinterpret_cast<char*>(derived_p) + offset);
  }

  void delete_pointer(const T* /*ptr*/,
      std::pmr::polymorphic_allocator<> alloc) const noexcept {
    (*operator_function_)(derived_ptr_, alloc, false);
  }

  operator_function_pointer operator_function() const noexcept {
    return operator_function_;
  }

   const void* get_derived_pointer(const T* /*ptr*/) const noexcept {
     return derived_ptr_;
   }
 private:
  operator_function_pointer operator_function_{nullptr};
  const void* derived_ptr_{nullptr};
};

template <std::move_constructible T>
    requires std::is_final_v<T>
class pointer_operator<T> {
 public:
  using operator_function_pointer =
      void* (*)(const void*, std::pmr::polymorphic_allocator<>, bool) noexcept;

  pointer_operator() noexcept = default;

  explicit pointer_operator(const T* /*derived_ptr*/) noexcept {}

  pointer_operator(const T* /*ptr*/, pointer_operator /*other*/) noexcept {}

  T* allocate_from(const T* other,
                   std::pmr::polymorphic_allocator<> alloc) noexcept {
    return alloc.new_object<T>(std::move(*const_cast<T*>(other)));
   }

  void delete_pointer(const T* other,
      std::pmr::polymorphic_allocator<> alloc) const noexcept {
    return alloc.delete_object(const_cast<T*>(other));
  }

   operator_function_pointer operator_function() const noexcept {
     return pointer_operator_function_v<T>;
   }

   const void* get_derived_pointer(const T* ptr) const noexcept {
     return static_cast<const void*>(ptr);
   }
};
}  // namespace bbai::memmg
