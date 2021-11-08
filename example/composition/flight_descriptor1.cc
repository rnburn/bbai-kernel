#include "flight_descriptor1.h"

namespace bbai::excmp {
//--------------------------------------------------------------------------------------------------
// constructor
//--------------------------------------------------------------------------------------------------
flight_descriptor1::flight_descriptor1(allocator_type alloc) noexcept
  : origin_{alloc}, destination_{alloc}
{}

flight_descriptor1::flight_descriptor1(std::pmr::string&& origin,
                                       std::pmr::string&& destination,
                                       allocator_type alloc)
    : origin_{std::move(origin), alloc},
      destination_{std::move(destination), alloc} {}

flight_descriptor1::flight_descriptor1(const flight_descriptor1& other,
                                       allocator_type alloc)
    : origin_{other.origin_, alloc}, destination_{other.destination_, alloc} {}

flight_descriptor1::flight_descriptor1(flight_descriptor1&& other,
                                       allocator_type alloc) noexcept
    : origin_{std::move(other.origin_), alloc},
      destination_{std::move(other.destination_), alloc} {}
} // namespace bbai::excmp
