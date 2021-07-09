#include "sum2.h"

#include "json_value.h"
#include "json_array2.h"
#include "json_number.h"

namespace bbai::jsonex {
static int sum_impl(const json_value& json) noexcept;

//--------------------------------------------------------------------------------------------------
// sum_array
//--------------------------------------------------------------------------------------------------
static int sum_array(const json_array2& array) noexcept {
  int res = 0;
  for (size_t i=0; i<array.size(); ++i) {
    res += sum_impl(array[i]);
  }
  return res;
}

//--------------------------------------------------------------------------------------------------
// sum_impl
//--------------------------------------------------------------------------------------------------
int sum_impl(const json_value& json) noexcept {
  switch (json.type()) {
    case json_value_type::number:
      return static_cast<const json_number&>(json).value();
    case json_value_type::array:
      return sum_array(static_cast<const json_array2&>(json));
  }
  __builtin_unreachable();
}

//--------------------------------------------------------------------------------------------------
// sum2
//--------------------------------------------------------------------------------------------------
int sum2(const json_value* json) noexcept {
  if (json == nullptr) {
    return 0;
  }
  return sum_impl(*json);
}
} // namespace bbai::jsonex
