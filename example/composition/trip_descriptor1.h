#pragma once

#include <memory_resource>
#include <span>
#include <string>
#include <string_view>
#include <vector>

#include "flight_descriptor1.h"

namespace bbai::excmp {
//--------------------------------------------------------------------------------------------------
// trip_descriptor1
//--------------------------------------------------------------------------------------------------
class trip_descriptor1 {
 public:
   using allocator_type = std::pmr::polymorphic_allocator<>;

   // constructor
   trip_descriptor1() noexcept = default;

   explicit trip_descriptor1(allocator_type alloc) noexcept;

   trip_descriptor1(int trip_id, std::pmr::string&& passenger_name,
                    std::pmr::vector<flight_descriptor1>&& legs,
                    allocator_type alloc = {});

   trip_descriptor1(const trip_descriptor1& other,
                    allocator_type = {});

   trip_descriptor1(trip_descriptor1&& other) noexcept = default;

   trip_descriptor1(trip_descriptor1&& other, allocator_type alloc) noexcept;

   // assignment
   trip_descriptor1& operator=(const trip_descriptor1&) = default;

   trip_descriptor1& operator=(trip_descriptor1&&) = default;

   // accessors
   allocator_type get_allocator() const noexcept {
     return passenger_name_.get_allocator();
   }

   int trip_id() const noexcept { return trip_id_; }

   std::string_view passenger_name() const noexcept { return passenger_name_; }

   std::span<const flight_descriptor1> legs() const noexcept { return legs_; }

  private:
   int trip_id_;
   std::pmr::string passenger_name_;
   std::pmr::vector<flight_descriptor1> legs_;
};
} // namespace bbai::excmp
