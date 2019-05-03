#include "stackext/linear_allocator.h"

#include "3rd_party/catch2/catch.hpp"

TEST_CASE("linear_allocator allocates memory in LIFO order.") {
  stackext::linear_allocator allocator{100};

  REQUIRE(allocator.max_size() == 100);
  REQUIRE(allocator.size() == 0);

  size_t num_bytes = 100;
  allocator.allocate(num_bytes);
  REQUIRE(allocator.size() == num_bytes);

  allocator.deallocate(num_bytes);
  REQUIRE(allocator.size() == 0);
}
