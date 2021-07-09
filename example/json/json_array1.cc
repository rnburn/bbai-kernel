#include "json_array1.h"

namespace bbai::jsonex {
//--------------------------------------------------------------------------------------------------
// to_string
//--------------------------------------------------------------------------------------------------
std::string json_array1::to_string() const noexcept {
  std::string res;
  res += '[';
  for (size_t i=0; i<values_.size(); ++i) {
    res += values_[i]->to_string();
    if (i < values_.size()-1) {
      res += ",";
    }
  }
  res += ']';
  return res;
}
} // namespace bbai::jsonex
