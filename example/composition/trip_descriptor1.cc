#include "trip_descriptor1.h"

namespace bbai::excmp {
//--------------------------------------------------------------------------------------------------
// constructor
//--------------------------------------------------------------------------------------------------
trip_descriptor1::trip_descriptor1(int trip_id,
                                   std::pmr::string&& passenger_name,
                                   std::pmr::vector<flight_descriptor1>&& legs,
                                   allocator_type alloc)
    : trip_id_{trip_id},
      passenger_name_{std::move(passenger_name), alloc},
      legs_{std::move(legs), alloc} {}
} // namespace bbai::excmp
