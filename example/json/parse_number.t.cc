#include "parse_number.h"

#include <string_view>

#include "bbai/base/test/unit_test.h"
using namespace bbai::jsonex;

TEST_CASE("we can parse a number") {
  SECTION("verify we parse a number correctly") {
    std::string_view s = "123 ,";
    REQUIRE(parse_number(s) == 123);
    REQUIRE((s == " ,"));
  }

  SECTION("we can parse a negative number that starts with +") {
    std::string_view s = "-123 ,";
    REQUIRE(parse_number(s) == -123);
    REQUIRE((s == " ,"));
  }
}
