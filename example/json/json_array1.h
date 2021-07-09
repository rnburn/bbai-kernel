#pragma once

#include <memory_resource>
#include <vector>

#include "json_value.h"

#include "bbai/memory/management/managed_ptr.h"

namespace bbai::jsonex {
//--------------------------------------------------------------------------------------------------
// json_array1
//--------------------------------------------------------------------------------------------------
class json_array1 final : public json_value {
  using vector_type =
      std::pmr::vector<memmg::managed_ptr<const json_value>>;

 public:
  using allocator_type = std::pmr::polymorphic_allocator<>;

  json_array1() noexcept = default;

  explicit json_array1(allocator_type alloc) noexcept : values_{alloc} {}

  explicit json_array1(vector_type&& values, allocator_type alloc = {}) noexcept
      : values_{std::move(values), alloc} {}

  allocator_type get_allocator() const noexcept {
    return values_.get_allocator();
  }

  json_array1(json_array1&& other) noexcept = default;

  json_array1(json_array1&& other, allocator_type alloc) noexcept
      : values_{std::move(other.values_), alloc} {}

  json_array1& operator=(json_array1&& other) noexcept = default;

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
