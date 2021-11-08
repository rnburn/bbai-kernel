#include <array>
#include <cstddef>
#include <iostream>
#include <memory_resource>

#include "trip_descriptor1.h"

using namespace bbai;
using namespace bbai::excmp;

int main() {
  int trip_id = 123;
  std::pmr::string name = "Indiana Jones";
  std::pmr::vector<flight_descriptor1> legs{
      {"New York", "Cairo"},
  };
  trip_descriptor1 trip{trip_id, std::move(name), std::move(legs)};

  std::array<std::byte, 1024> buffer;
  std::pmr::monotonic_buffer_resource resource{
      static_cast<void*>(buffer.data()), buffer.size()};

  trip_descriptor1 trip_p{std::move(trip), &resource};
  if (trip_p.get_allocator() != std::pmr::polymorphic_allocator<>{&resource}) {
    std::cerr << "allocator incorrect\n";
    return -1;
  }
  auto& flight = trip_p.legs()[0];
  std::cout << flight.origin() << ": "
            << (reinterpret_cast<const std::byte*>(flight.origin().data()) -
                buffer.data())
            << "\n";
  std::cout << flight.destination() << ": "
            << (reinterpret_cast<const std::byte*>(
                    flight.destination().data()) -
                buffer.data())
            << "\n";
  return 0;
}
