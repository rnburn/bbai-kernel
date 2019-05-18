#include "stackext/linear_allocator.h"

#include "3rd_party/catch2/catch.hpp"

TEST_CASE("linear_allocator satisfies C++'s Allocator concept") {
  stackext::stack_allocator base_allocator{100};

  SECTION("We can use linear_allocator with standard C++ containers") {
    stackext::scoped_allocator allocator{base_allocator};

    std::vector<double, stackext::linear_allocator<double>> v(stackext::linear_allocator<double>{allocator});
    v.push_back(1.0);
    v.push_back(2.0);
    REQUIRE(v[0] == 1.0);
    REQUIRE(v[1] == 2.0);
    REQUIRE(base_allocator.size() >= 2*sizeof(double));
  }
  REQUIRE(base_allocator.size() == 0);
}
