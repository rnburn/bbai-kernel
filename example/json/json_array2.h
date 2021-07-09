#pragma once

#include <memory>
#include <vector>

#include "json_value.h"

namespace bbai::jsonex {
//--------------------------------------------------------------------------------------------------
// json_array2
//--------------------------------------------------------------------------------------------------
class json_array2 final : public json_value {
  using vector_type =
      std::vector<std::unique_ptr<const json_value>>;

 public:
  json_array2() noexcept = default;

  explicit json_array2(vector_type&& values) noexcept
      : values_{std::move(values)} {}

  size_t size() const noexcept { return values_.size(); }

  const json_value& operator[](size_t index) const noexcept {
    return *values_[index];
  }

  // json_value
  json_value_type type() const noexcept override {
    return json_value_type::array;
  }

  std::string to_string() const noexcept override;

 private:
  vector_type values_;
};
} // namespace bbai::jsonex
