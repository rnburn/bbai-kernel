#pragma once

#include <type_traits>
#include <tuple>

#include "bbai/base/reflection/tuple_convertible_arity.h"
#include "bbai/base/reflection/tuple_conversion.h"
#include "bbai/base/type/uncvref.h"

namespace bbai::basrf {
//--------------------------------------------------------------------------------------------------
// element_t
//--------------------------------------------------------------------------------------------------
template <size_t I, class T>
using element_t = bast::uncvref_t<
    std::tuple_element_t<I, decltype(as_tuple(std::declval<T>()))>>;
} // namespace bbai::basrf
