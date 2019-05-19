#pragma once

#include "stackext/scoped_allocator.h"

namespace stackext {
template <class T>
class linear_allocator {
  template <class U>
  friend class linear_allocator;
 public:
   using value_type = T;

   explicit linear_allocator(scoped_allocator& base_allocator) noexcept
     : base_allocator_{base_allocator} {}

   template <class U>
   linear_allocator(const linear_allocator<U>& other) noexcept
    : base_allocator_{other.base_allocator_}
   {}

   T* allocate(size_t n) const {
     return static_cast<T*>(base_allocator_.allocate<alignof(T)>(sizeof(T)*n));
   }

   void deallocate(T* /*ptr*/, size_t /*n*/) const {
     // Memory will be deallocated from scoped_allocator's destructor
   }

 private:
   scoped_allocator& base_allocator_;
};

template <class T, class U>
bool operator==(const linear_allocator<T>& lhs, const linear_allocator<U>& rhs) noexcept {
  return true;
}

template <class T, class U>
bool operator!=(const linear_allocator<T>& lhs, const linear_allocator<U>& rhs) noexcept {
  return !(lhs == rhs);
}
} // namespace stackext
