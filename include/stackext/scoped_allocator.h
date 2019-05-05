#pragma once

#include <cstdlib>
#include <memory>
#include <type_traits>

#include "stackext/stack_allocator.h"
#include "stackext/utility.h"

namespace stackext {
class scoped_allocator {
  struct heap_allocation {
    heap_allocation* next;
  };

  struct dtor_invocation {
    void (*invoker)(void* data, size_t size) noexcept;
    size_t n;
    dtor_invocation* next;
  };

 public:
  explicit scoped_allocator(stack_allocator& base_allocator) noexcept
      : base_allocator_{base_allocator} {}

  ~scoped_allocator() noexcept;

  scoped_allocator(const scoped_allocator&) = delete;
  scoped_allocator(scoped_allocator&&) = delete;

  scoped_allocator& operator=(const scoped_allocator&) = delete;
  scoped_allocator& operator=(scoped_allocator&&) = delete;

  template <size_t Alignment>
  void* allocate(size_t num_bytes);

  template <class T, class... Args,
            typename std::enable_if<std::is_trivially_destructible<T>::value,
                                    void*>::type = nullptr>
  T* allocate(size_t n, Args&&... args);

  template <class T, class... Args,
            typename std::enable_if<!std::is_trivially_destructible<T>::value,
                                    void*>::type = nullptr>
  T* allocate(size_t n, Args&&... args);

 private:
  stack_allocator& base_allocator_;
  size_t size_{0};
  heap_allocation* heap_allocations_{nullptr};
  dtor_invocation* dtor_invocations_{nullptr};

  template <size_t Alignment>
  void* allocate_from_heap(size_t num_bytes);
};

inline scoped_allocator::~scoped_allocator() noexcept {
  auto dtor_invocation = dtor_invocations_;
  while (dtor_invocation != nullptr) {
    (*dtor_invocation->invoker)(static_cast<void*>(dtor_invocation),
                                dtor_invocation->n);
    dtor_invocation = dtor_invocation->next;
  }

  auto heap_allocation = heap_allocations_;
  while (heap_allocation != nullptr) {
    auto next = heap_allocation->next;
    std::free(static_cast<void*>(heap_allocation));
    heap_allocation = next;
  }

  base_allocator_.deallocate(size_);
}

template <size_t Alignment>
void* scoped_allocator::allocate(size_t num_bytes) {
  static_assert(is_power_of_2(Alignment));

  auto free_space_start = base_allocator_.max_size() - base_allocator_.size();
  auto free_space = free_space_start;
  auto result = base_allocator_.top();
  if (std::align(Alignment, num_bytes, result, free_space) != nullptr) {
    free_space -= num_bytes;
    auto size = free_space_start - free_space;
    size_ += size;
    base_allocator_.allocate(size);
    return result;
  }

  return this->allocate_from_heap<Alignment>(num_bytes);
}

template <class T, class... Args,
          typename std::enable_if<std::is_trivially_destructible<T>::value,
                                  void*>::type>
T* scoped_allocator::allocate(size_t n, Args&&... args) {
  auto result = static_cast<T*>(allocate<alignof(T)>(n * sizeof(T)));
  construct(result, result + n, std::forward<Args>(args)...);
  return result;
}

template <class T, class... Args, typename std::enable_if<
                       !std::is_trivially_destructible<T>::value, void*>::type>
T* scoped_allocator::allocate(size_t n, Args&&... args) {
  static constexpr auto alignment = alignof(dtor_invocation) > alignof(T)
                                   ? alignof(dtor_invocation)
                                   : alignof(T);
  static constexpr auto allocation_offset = 
    align_up<alignment>(sizeof(dtor_invocation));
  auto size = allocation_offset + sizeof(T)*n;
  auto data = this->allocate<alignment>(size);
  auto result = reinterpret_cast<T*>(static_cast<char*>(data) + allocation_offset);
  construct(result, result + n, std::forward<Args>(args)...);
  auto dtor_invocation = static_cast<scoped_allocator::dtor_invocation*>(data);
  dtor_invocation->invoker = [](void* data, size_t n) noexcept {
    auto iter =
        reinterpret_cast<T*>(static_cast<char*>(data) + allocation_offset);
    destroy(iter, iter+n);
  };
  dtor_invocation->n = n;
  dtor_invocation->next = dtor_invocations_;
  dtor_invocations_ = dtor_invocation;

  return result;
}

template <size_t Alignment>
void* scoped_allocator::allocate_from_heap(size_t num_bytes) {
  auto size = sizeof(heap_allocation);
  size = align_up<Alignment>(size);
  auto allocation_offset = size;
  size += num_bytes;
  auto data = std::malloc(size);
  if (data == nullptr) {
    throw std::bad_alloc{};
  }
  auto heap_allocation = static_cast<scoped_allocator::heap_allocation*>(data);
  heap_allocation->next = heap_allocations_;
  heap_allocations_ = heap_allocation;
  return static_cast<void*>(static_cast<char*>(data) + allocation_offset);
}
}  // namespace stackext
