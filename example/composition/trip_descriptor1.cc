#include "trip_descriptor1.h"

namespace bbai::excmp {
//--------------------------------------------------------------------------------------------------
// constructor
//--------------------------------------------------------------------------------------------------
trip_descriptor1::trip_descriptor1(allocator_type alloc) noexcept
    : trip_id_{}, passenger_name_{alloc}, legs_{alloc} {}

trip_descriptor1::trip_descriptor1(int trip_id,
                                   std::pmr::string&& passenger_name,
                                   std::pmr::vector<flight_descriptor1>&& legs,
                                   allocator_type alloc)
    : trip_id_{trip_id},
      passenger_name_{std::move(passenger_name), alloc},
      legs_{std::move(legs), alloc} {}

trip_descriptor1::trip_descriptor1(const trip_descriptor1& other,
                                   allocator_type alloc)
    : trip_id_{other.trip_id_},
      passenger_name_{other.passenger_name_, alloc},
      legs_{other.legs_, alloc} {}

trip_descriptor1::trip_descriptor1(trip_descriptor1&& other,
                                   allocator_type alloc) noexcept
    : trip_id_{other.trip_id_},
      passenger_name_{std::move(other.passenger_name_), alloc},
      legs_{std::move(other.legs_), alloc} {}
}  // namespace bbai::excmp
