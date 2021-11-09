#pragma once

#include <memory_resource>
#include <string>
#include <string_view>

#include "bbai/base/memory/allocator_aware_helper.h"

namespace bbai::excmp {
//--------------------------------------------------------------------------------------------------
// flight_descriptor2_data
//--------------------------------------------------------------------------------------------------
struct flight_descriptor2_data {
  std::pmr::string origin_;
  std::pmr::string destination_;
};

//--------------------------------------------------------------------------------------------------
// flight_descriptor2
//--------------------------------------------------------------------------------------------------
class flight_descriptor2 final
    : public basm::allocator_aware_helper<flight_descriptor2_data> {
  using base = basm::allocator_aware_helper<flight_descriptor2_data>;

 public:
  // constructor
  using base::base;

  explicit flight_descriptor2(flight_descriptor2_data&&,
                              allocator_type) noexcept = delete;

  flight_descriptor2(std::pmr::string&& origin, std::pmr::string&& destination,
                     allocator_type alloc = {});

  // accessors
  std::string_view origin() const noexcept { return origin_; }

  std::string_view destination() const noexcept { return destination_; }
};
} // namespace bbai::excmp
