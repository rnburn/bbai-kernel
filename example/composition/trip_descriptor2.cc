#include "trip_descriptor2.h"

namespace bbai::excmp {
//--------------------------------------------------------------------------------------------------
// constructor
//--------------------------------------------------------------------------------------------------
trip_descriptor2::trip_descriptor2(int trip_id,
                                   std::pmr::string&& passenger_name,
                                   std::pmr::vector<flight_descriptor2>&& legs,
                                   allocator_type alloc)
    : base{trip_descriptor2_data{
               .trip_id_{trip_id},
               .passenger_name_{std::move(passenger_name)},
               .legs_{std::move(legs)},
           },
           alloc} {}
}  // namespace bbai::excmp
