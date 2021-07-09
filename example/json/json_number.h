#pragma once

#include <string>

#include "json_value.h"

namespace bbai::jsonex {
//--------------------------------------------------------------------------------------------------
// json_number
//--------------------------------------------------------------------------------------------------
class json_number final : public json_value {
 public:
  explicit json_number(int value) noexcept : value_{value} {}

  int value() const noexcept { return value_; }

  // json_value
  json_value_type type() const noexcept override { return json_value_type::number; }

  std::string to_string() const noexcept override { return std::to_string(value_); }

 private:
  int value_;
};
} // namespace bbai::jsonex
