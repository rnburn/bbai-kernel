#pragma once

#include <memory_resource>
#include <string>
#include <string_view>

namespace bbai::excmp {
//--------------------------------------------------------------------------------------------------
// flight_descriptor1
//--------------------------------------------------------------------------------------------------
class flight_descriptor1 {
 public:
  using allocator_type = std::pmr::polymorphic_allocator<>;

  // constructor
  flight_descriptor1() noexcept = default;

  flight_descriptor1(allocator_type alloc) noexcept;

  flight_descriptor1(std::pmr::string&& origin, std::pmr::string&& destination,
                     allocator_type alloc = {});

  flight_descriptor1(const flight_descriptor1& other, allocator_type alloc = {});

  flight_descriptor1(flight_descriptor1&& other) = default;

  flight_descriptor1(flight_descriptor1&& other, allocator_type alloc = {}) noexcept;

  // assignment
  flight_descriptor1& operator=(const flight_descriptor1&) = default;

  flight_descriptor1& operator=(flight_descriptor1&&) = default;


  // accessors
  allocator_type get_allocator() const noexcept { return origin_.get_allocator(); }

  std::string_view origin() const noexcept { return origin_; }

  std::string_view destination() const noexcept { return destination_; }

 private:
  std::pmr::string origin_;
  std::pmr::string destination_;
};
} // namespace bbai::excmp
