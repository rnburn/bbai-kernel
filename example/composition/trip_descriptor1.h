#pragma once

#include <memory_resource>
#include <string>
#include <vector>

#include "flight_descriptor1.h"

namespace bbai::excmp {
//--------------------------------------------------------------------------------------------------
// trip_descriptor1
//--------------------------------------------------------------------------------------------------
class trip_descriptor1 {
 public:
   using allocator_type = std::pmr::polymorphic_allocator<>;

   trip_descriptor1(
       int trip_id,
       std::pmr::string&& passenger_name,
       std::pmr::vector<flight_descriptor1>&& legs,
       allocator_type alloc = {});

 private:
  int trip_id_;
  std::pmr::string passenger_name_;
  std::pmr::vector<flight_descriptor1> legs_;
};
} // namespace bbai::excmp
