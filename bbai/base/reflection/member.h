#pragma once

#include <cstddef>

#include "bbai/base/type/fixed_string.h"

namespace bbai::basrf {
//--------------------------------------------------------------------------------------------------
// member_index_impl
//--------------------------------------------------------------------------------------------------
namespace detail {
template <size_t, class, template <size_t, class> class>
struct member_index_impl {
  static constexpr size_t value = 0;
};

template <size_t I, class M, template <size_t, class> class T>
  requires requires {
    T<I, M>::name;
  }
struct member_index_impl<I, M, T> {
  static constexpr size_t value = 1 + member_index_impl<I+1, M, T>::value;
};
} // namespace detail

//--------------------------------------------------------------------------------------------------
// member_index
//--------------------------------------------------------------------------------------------------
namespace detail {
template <class M, template <size_t, class> class T>
struct member_index {
  static constexpr size_t value = member_index_impl<0, M, T>::value;
};
} // namespace detail

//--------------------------------------------------------------------------------------------------
// num_members_v
//--------------------------------------------------------------------------------------------------
template <class T>
constexpr size_t num_members_v =
    detail::member_index<struct bbai_detail_member_tag,
                         T::template bbai_detail_member_reflection>::value;

//--------------------------------------------------------------------------------------------------
// member_name_v
//--------------------------------------------------------------------------------------------------
template <class T, size_t I>
constexpr auto member_name_v = T::template bbai_detail_member_reflection<
    I, struct bbai_detail_member_tag>::name;

//--------------------------------------------------------------------------------------------------
// member_type_t
//--------------------------------------------------------------------------------------------------
template <class T, size_t I>
using member_type_t = typename T::template bbai_detail_member_reflection<
    I, struct bbai_detail_member_tag>::type;

//--------------------------------------------------------------------------------------------------
// member_get
//--------------------------------------------------------------------------------------------------
template <size_t I, class T>
auto& member_get(T& a) noexcept {
  constexpr auto ptr = T::template bbai_detail_member_reflection<
      I, struct bbai_detail_member_tag>::template offset_v<T>;
  return a.*ptr;
}

template <size_t I, class T>
const auto& member_get(const T& a) noexcept {
  constexpr auto ptr = T::template bbai_detail_member_reflection<
      I, struct bbai_detail_member_tag>::template offset_v<T>;
  return a.*ptr;
}

//--------------------------------------------------------------------------------------------------
// BBAI_REFLECT_MEMBER
//--------------------------------------------------------------------------------------------------
#define BBAI_REFLECT_MEMBER(NAME, ...)                                         \
  __VA_ARGS__ NAME;                                                            \
  template <size_t, class>                                                     \
  struct bbai_detail_member_reflection;                                        \
  static constexpr size_t bbai_detail_##NAME##_member_index =                  \
      bbai::basrf::detail::member_index<struct bbai_detail_##NAME##_tag,       \
                                        bbai_detail_member_reflection>::value; \
  template <class T>                                                           \
  struct bbai_detail_member_reflection<bbai_detail_##NAME##_member_index, T> { \
    static constexpr bast::fixed_string name = #NAME;                          \
    using type = __VA_ARGS__;                                                  \
    template <class U>                                                         \
    static constexpr type U::*offset_v = &U::NAME;                             \
  };
} // namespace bbai::basrf
