#pragma once

#include <concepts>
#include <memory_resource>
#include <tuple>
#include <utility>

#include "bbai/base/concept/allocator_aware.h"
#include "bbai/base/reflection/tuple_convertible_arity.h"
#include "bbai/base/reflection/tuple_convertible_get.h"
#include "bbai/base/reflection/tuple_conversion.h"
#include "bbai/base/reflection/element.h"
#include "bbai/base/type/uncvref.h"

namespace bbai::basm {
//--------------------------------------------------------------------------------------------------
// make_allocator_aware_default_initializer
//--------------------------------------------------------------------------------------------------
namespace detail {
template <class T>
T make_allocator_aware_default_initializer(std::pmr::polymorphic_allocator<> alloc) noexcept {
  if constexpr (basc::allocator_aware<T>) {
    return T{alloc};
  } else {
    return T{};
  }
}
} // namespace detail

//--------------------------------------------------------------------------------------------------
// make_allocator_aware_copy_constructor_initializer
//--------------------------------------------------------------------------------------------------
namespace detail {
template <class T>
T make_allocator_aware_copy_constructor_initializer(const T& other, std::pmr::polymorphic_allocator<> alloc) noexcept {
  if constexpr (basc::allocator_aware<T>) {
    return T{other, alloc};
  } else {
    return T{other};
  }
}
} // namespace detail

//--------------------------------------------------------------------------------------------------
// make_allocator_aware_move_constructor_initializer
//--------------------------------------------------------------------------------------------------
namespace detail {
template <class T>
T make_allocator_aware_move_constructor_initializer(T& other, std::pmr::polymorphic_allocator<> alloc) noexcept {
  if constexpr (basc::allocator_aware<T>) {
    return T{std::move(other), alloc};
  } else {
    return T{std::move(other)};
  }
}
} // namespace detail

//--------------------------------------------------------------------------------------------------
// get_allocator
//--------------------------------------------------------------------------------------------------
namespace detail {
template <class TFirst, class... TRest>
std::pmr::polymorphic_allocator<> get_allocator(const TFirst& x, const TRest&... xs) noexcept {
  if constexpr (basc::allocator_aware<TFirst>) {
    return x.get_allocator();
  } else {
    return detail::get_allocator(xs...);
  }
}
} // namespace detail

//--------------------------------------------------------------------------------------------------
// allocator_aware_impl
//--------------------------------------------------------------------------------------------------
namespace detail {
template <class, class>
class allocator_aware_impl;

template <class Data, size_t... Indexes>
class allocator_aware_impl<Data, std::index_sequence<Indexes...>> : protected Data {
 public:
   using allocator_type = std::pmr::polymorphic_allocator<>;

   allocator_aware_impl() noexcept = default;

   explicit allocator_aware_impl(allocator_type alloc) noexcept
       : Data{make_allocator_aware_default_initializer<
             basrf::element_t<Indexes, Data>>(alloc)...

         } {}

   allocator_aware_impl(const allocator_aware_impl &other,
                        allocator_type alloc = {}) noexcept
     requires std::copy_constructible<Data>
       : Data{make_allocator_aware_copy_constructor_initializer(
             basrf::tuple_convertible_get<Indexes>(static_cast<const Data &>(other)),
             alloc)...} {}

   allocator_aware_impl(allocator_aware_impl&& other) noexcept = default;

   allocator_aware_impl(allocator_aware_impl &&other,
                        allocator_type alloc) noexcept
       : Data{make_allocator_aware_move_constructor_initializer(
             basrf::tuple_convertible_get<Indexes>(static_cast<Data &>(other)),
             alloc)...} {}

   allocator_aware_impl &operator=(const allocator_aware_impl &rhs) noexcept
       requires std::copy_constructible<Data>
   = default;

   allocator_aware_impl& operator=(allocator_aware_impl&& rhs) noexcept = default;

   allocator_type get_allocator() const noexcept {
     return detail::get_allocator(
         basrf::tuple_convertible_get<Indexes>(static_cast<const Data &>(*this))...);
   }
};
} // namespace detail

//--------------------------------------------------------------------------------------------------
// allocator_aware_helper
//--------------------------------------------------------------------------------------------------
template <class Data>
class allocator_aware_helper
    : public detail::allocator_aware_impl<
          Data, std::make_index_sequence<basrf::tuple_convertible_arity_v<Data>>> {
public:
  using detail::allocator_aware_impl<
      Data, std::make_index_sequence<basrf::tuple_convertible_arity_v<Data>>>::
      allocator_aware_impl;
};
} // namespace bbai::basm
