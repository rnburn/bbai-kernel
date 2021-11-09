#pragma once

#include <span>
#include <string>
#include <string_view>
#include <vector>

#include "bbai/base/memory/allocator_aware_helper.h"

#include "flight_descriptor2.h"

namespace bbai::excmp {
//--------------------------------------------------------------------------------------------------
// trip_descriptor2_data
//--------------------------------------------------------------------------------------------------
struct trip_descriptor2_data {
   int trip_id_;
   std::pmr::string passenger_name_;
   std::pmr::vector<flight_descriptor2> legs_;
};

//--------------------------------------------------------------------------------------------------
// trip_descriptor2
//--------------------------------------------------------------------------------------------------
class trip_descriptor2 final
    : public basm::allocator_aware_helper<trip_descriptor2_data> {
  using base = basm::allocator_aware_helper<trip_descriptor2_data>;

 public:
  // constructor
  using base::base;

  trip_descriptor2(int trip_id, std::pmr::string&& passenger_name,
                   std::pmr::vector<flight_descriptor2>&& legs,
                   allocator_type alloc = {});

  // accessors
  int trip_id() const noexcept { return trip_id_; }

  std::string_view passenger_name() const noexcept { return passenger_name_; }

  std::span<const flight_descriptor2> legs() const noexcept { return legs_; }
};
}  // namespace bbai::excmp
