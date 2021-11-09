#include "flight_descriptor2.h"

namespace bbai::excmp {
//--------------------------------------------------------------------------------------------------
// constructor
//--------------------------------------------------------------------------------------------------
flight_descriptor2::flight_descriptor2(std::pmr::string&& origin,
                                       std::pmr::string&& destination,
                                       allocator_type alloc)
    : base{flight_descriptor2_data{.origin_{std::move(origin)},
                                   .destination_{std::move(destination)}},
           alloc} {}
}  // namespace bbai::excmp
