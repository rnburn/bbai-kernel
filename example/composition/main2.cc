#include <array>
#include <cstddef>
#include <iostream>
#include <memory_resource>

#include "trip_descriptor2.h"

using namespace bbai;
using namespace bbai::excmp;

int main() {
  int trip_id = 123;
  std::pmr::string name = "Indiana Jones";
  std::pmr::vector<flight_descriptor2> legs{
      {"New York", "Cairo"},
  };
  trip_descriptor2 trip{trip_id, std::move(name), std::move(legs)};

  std::array<std::byte, 1024> buffer;
  std::pmr::monotonic_buffer_resource resource{
      static_cast<void*>(buffer.data()), buffer.size()};

  trip_descriptor2 trip_p{std::move(trip), &resource};
  if (trip_p.get_allocator() != std::pmr::polymorphic_allocator<>{&resource}) {
    std::cerr << "allocator incorrect\n";
    return -1;
  }
  auto& flight = trip_p.legs()[0];

  auto origin = flight.origin();
  auto origin_offset =
      reinterpret_cast<const std::byte*>(origin.data()) - buffer.data();
  std::cout << origin << "\t" << origin_offset << "\n";
  if (origin_offset < 0 || origin_offset >= std::ssize(buffer)) {
    std::cerr << "offset wrong\n";
    return -1;
  }

  auto destination = flight.destination();
  auto destination_offset =
      reinterpret_cast<const std::byte*>(destination.data()) - buffer.data();
  std::cout << destination << "\t" << destination_offset << "\n";
  if (destination_offset < 0 || destination_offset >= std::ssize(buffer)) {
    std::cerr << "offset wrong\n";
    return -1;
  }

  return 0;
}

