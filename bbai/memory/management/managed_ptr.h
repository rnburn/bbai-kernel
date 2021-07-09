#pragma once

#include <compare>
#include <concepts>
#include <memory_resource>
#include <type_traits>

#include "bbai/memory/management/pointer_operator.h"

namespace bbai::memmg {
//--------------------------------------------------------------------------------------------------
// managed_ptr
//--------------------------------------------------------------------------------------------------
template <class T>
class managed_ptr {
  using pointer_operator_type = pointer_operator<std::remove_const_t<T>>;
  using reference = std::add_lvalue_reference_t<T>;
 public:
   using allocator_type = std::pmr::polymorphic_allocator<>;
   using element_type = T;
   using pointer = T*;

   managed_ptr() noexcept = default;

   ~managed_ptr() noexcept {
     this->reset();
   }

   explicit managed_ptr(allocator_type alloc) noexcept
     : alloc_{alloc}
   {}

   managed_ptr(const managed_ptr&) = delete;

   template <class U>
      requires std::convertible_to<U*, pointer>
   managed_ptr(managed_ptr<U>&& other) noexcept
       : alloc_{other.alloc_}, operator_{other.ptr_, other.operator_}, ptr_{other.release()} {
   }

   template <class U>
      requires std::convertible_to<U*, pointer>
   managed_ptr(managed_ptr<U>&& other, allocator_type alloc) noexcept
       : alloc_{alloc} {
     this->move_assign(std::move(other));
   }

   template <std::move_constructible U>
      requires std::convertible_to<U*, pointer>
   managed_ptr(U* ptr, allocator_type alloc = {}) noexcept
       : alloc_{alloc}, operator_{ptr}, ptr_{ptr} {}

   managed_ptr(std::nullptr_t, allocator_type alloc = {}) noexcept
     : alloc_{alloc}, operator_{}
   {}

   managed_ptr& operator=(const managed_ptr& other) = delete;

   managed_ptr& operator=(managed_ptr&& other) noexcept {
     this->move_assign(std::move(other));
     return *this;
   }

   reference operator*() const noexcept 
     requires (!std::is_void_v<T>)
   {
     return *ptr_;
   }

   T* get() const noexcept { return ptr_; }

   T* operator->() const noexcept 
     requires (!std::is_void_v<T>)
   { 
     return ptr_; 
   }
  
   T* release() noexcept { 
     auto ptr = ptr_;
     ptr_ = nullptr;
     return ptr;
   }

   allocator_type get_allocator() const noexcept {
     return alloc_;
   }

   void reset() noexcept {
     if (ptr_ == nullptr) {
       return;
     }
     operator_.delete_pointer(ptr_, alloc_);
     ptr_ = nullptr;
   }

   bool operator==(std::nullptr_t) const noexcept {
     return ptr_ == nullptr;
   }

  template <class U>
    requires std::equality_comparable_with<pointer, U*>
  bool operator==(const managed_ptr<U>& other) const noexcept {
    return ptr_ == other.ptr_;
  }

  template<class U>
    requires std::three_way_comparable_with<pointer, U*>
  auto operator<=>(const managed_ptr<U>& other) const noexcept {
    return ptr_ <=> other.ptr_;
  }

   explicit operator bool() const noexcept {
     return ptr_ != nullptr;
   }

 private:
   allocator_type alloc_;
   [[no_unique_address]] pointer_operator_type operator_;
   T * ptr_{nullptr};

   template <class U>
   void move_assign(managed_ptr<U>&& other) noexcept {
     if (other.ptr_ == nullptr) {
       return;
     }
     operator_ = pointer_operator_type{other.ptr_, other.operator_};
     if (alloc_ == other.alloc_) {
       ptr_ = other.release();
     } else {
       ptr_ = operator_.allocate_from(other.ptr_, alloc_);
       other.reset();
     }
   }

   template <class U>
   friend class managed_ptr;
};
} // namespace bbai::memmg
