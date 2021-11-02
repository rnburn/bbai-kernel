#pragma once

#include <type_traits>

namespace bbai::bast {
//------------------------------------------------------------------------------
// uncvref_t
//------------------------------------------------------------------------------
template <class T>
using uncvref_t = typename std::remove_cv_t<std::remove_reference_t<T>>;
} // namespace bbai::bast
