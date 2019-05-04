#pragma once

#include <cstddef>
#include <cstdint>
#include <type_traits>
#include <utility>

namespace stackext {
constexpr bool is_power_of_2(size_t x) {
  // See https://stackoverflow.com/a/108329/4447365
  return x != 0 && !(x & (x - 1));
}
template <size_t Alignment>
constexpr int64_t align_up(int64_t x) {
  static_assert(is_power_of_2(Alignment));

  // See https://stackoverflow.com/a/4840428/4447365
  return (x + (static_cast<int64_t>(Alignment) - 1)) & -static_cast<int64_t>(Alignment);
}

template <size_t Alignment>
constexpr size_t align_up(size_t x) {
  return static_cast<size_t>(align_up<Alignment>(static_cast<int64_t>(x)));
}

template <class T, typename std::enable_if<
                       std::is_trivially_destructible<T>::value, void*>::type = nullptr>
void destroy(T* /*iter*/, T* /*last*/) noexcept {
}

template <class T, typename std::enable_if<
                       !std::is_trivially_destructible<T>::value, void*>::type = nullptr>
void destroy(T* first, T* last) noexcept {
  while (last != first) {
    --last;
    last->~T();
  }
}

template <class T, typename std::enable_if<
                       std::is_trivially_constructible<T>::value, void*>::type = nullptr>
void construct(T* /*iter*/, T* /*last*/) noexcept {
}

template <class T, class... Args,
          typename std::enable_if<
              !std::is_trivially_constructible<T, Args...>::value &&
                  std::is_nothrow_constructible<T, Args...>::value,
              void*>::type = nullptr>
void construct(T* iter, T* last, Args&&... args) noexcept {
  for (; iter != last; ++iter) {
    new (iter) T(std::forward<Args>(args)...);
  }
}

template <class T, class... Args,
          typename std::enable_if<
              !std::is_trivially_constructible<T, Args...>::value &&
                  !std::is_nothrow_constructible<T, Args...>::value,
              void*>::type = nullptr>
void construct(T* iter, T* last, Args&&... args) {
  auto first = iter;
  for (; iter != last; ++iter) {
    try {
      new (iter) T(std::forward<Args>(args)...);
    } catch (...) {
      destroy(first, iter);
      throw;
    }
  }
}
}  // namespace stackext
