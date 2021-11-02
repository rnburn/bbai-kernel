#pragma once

#include <type_traits>

#include "bbai/base/reflection/tuple_conversion.h"
#include "bbai/base/reflection/tuple_convertible_arity.h"
#include "bbai/base/type/uncvref.h"

namespace bbai::basrf {
//--------------------------------------------------------------------------------------------------
// tuple_convertible_get
//--------------------------------------------------------------------------------------------------
template <size_t I, class T>
  requires std::is_aggregate_v<bast::uncvref_t<T>> && (I < tuple_convertible_arity_v<T>)
decltype(auto) tuple_convertible_get(T&& aggregate) noexcept {
  auto t = as_tuple(aggregate);
  return std::get<I>(t);
}
} // namespace bbai::basrf
