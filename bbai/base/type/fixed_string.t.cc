#include "bbai/base/type/fixed_string.h"

#include <string>

#include "bbai/base/test/unit_test.h"
using namespace bbai;
using namespace bbai::bast;

TEST_CASE("fixed_string can be used as a compile-time string constant") {
  SECTION("rR5e", "we can declarse a fixed string") {
    static constexpr fixed_string s = "abc";
    REQUIRE(std::string{s} == "abc");
  }
}
