#include "bbai/memory/resource/counting_resource.h"

#include <memory_resource>

#include "bbai/base/test/unit_test.h"
using namespace bbai;
using namespace bbai::memr;

TEST_CASE("counting_resource tracks the number of bytes allocated") {

  SECTION("the count is greater than 0 upon allocation and equals 0 when everything is freed") {
    memr::counting_resource upstream;
    REQUIRE(upstream.count() == 0);
    {
      std::pmr::monotonic_buffer_resource resource{&upstream};
      REQUIRE(resource.allocate(10, 4) != nullptr);
      REQUIRE(upstream.count() >= 10);
    }
    REQUIRE(upstream.count() == 0);
  }
}
