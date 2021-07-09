#pragma once

#include <string>

#include "json_value_type.h"

namespace bbai::jsonex {
//--------------------------------------------------------------------------------------------------
// json_value
//--------------------------------------------------------------------------------------------------
class json_value {
 public:
   virtual ~json_value() noexcept = default;

   virtual json_value_type type() const noexcept = 0;

   virtual std::string to_string() const noexcept = 0;
};
} // namespace bbai::jsonex
