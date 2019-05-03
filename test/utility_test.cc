#include "stackext/utility.h"

#include "3rd_party/catch2/catch.hpp"

TEST_CASE("stackext::is_power_of_2 tests whether a number is a power of 2.") {
  REQUIRE(stackext::is_power_of_2(1));
  REQUIRE(stackext::is_power_of_2(2));
  REQUIRE(!stackext::is_power_of_2(3));
  REQUIRE(stackext::is_power_of_2(4));
  REQUIRE(!stackext::is_power_of_2(5));
}

TEST_CASE("align_up increases a number until it aligns to a given value.") {
  REQUIRE(stackext::align_up<4>(int64_t{0}) == 0);
  REQUIRE(stackext::align_up<4>(int64_t{1}) == 4);
  REQUIRE(stackext::align_up<4>(int64_t{2}) == 4);
  REQUIRE(stackext::align_up<4>(int64_t{3}) == 4);
  REQUIRE(stackext::align_up<4>(int64_t{4}) == 4);
}
