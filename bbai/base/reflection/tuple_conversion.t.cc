#include "bbai/base/reflection/tuple_conversion.h"

#include "bbai/base/test/unit_test.h"
using namespace bbai;
using namespace bbai::basrf;

struct a1 {
  int x;
  double y;
};

TEST_CASE("we can manipulate aggregates as tuples") {
  SECTION("TnQw", "we can modify aggregate members through the tuple decomposition") {
    a1 a;
    auto t = as_tuple(a);
    std::get<0>(t) = 10;
    REQUIRE(a.x == 10);

    std::get<1>(t) = 3.5;
    REQUIRE(a.y == 3.5);
  }
}
