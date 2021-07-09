#include "bbai/memory/resource/stackext_resource.h"

#include <memory_resource>

#include "bbai/memory/resource/counting_resource.h"
#include "bbai/memory/resource/stack_extension.h"
#include "bbai/base/test/unit_test.h"
using namespace bbai;
using namespace bbai::memr;

TEST_CASE("stackext_resource allocates from extended stack space") {
  const auto capacity = stack_extension::capacity();

  SECTION("memory is released on destruction") {
    {
      stackext_resource resource;
      REQUIRE(resource.allocate(10, 4) != nullptr);
      REQUIRE(stack_extension::size() == 10);
    }
    REQUIRE(stack_extension::size() == 0);
  }

  SECTION("memory is aligned") {
    stackext_resource resource;
    REQUIRE(resource.allocate(3, 1) != nullptr);
    REQUIRE(stack_extension::size() == 3);
    REQUIRE(resource.allocate(4, 4) != nullptr);
    REQUIRE(stack_extension::size() == 8);
  }

  SECTION("when stack space is exhausted, memory is taken from upstream") {
    counting_resource upstream;
    { 
      stackext_resource resource{&upstream}; 
      REQUIRE(resource.allocate(capacity + 1, 4) != nullptr);
      REQUIRE(upstream.count() > capacity);
    }
    REQUIRE(upstream.count() == 0);
  }

  SECTION("we can force a release of allocated memory") {
    counting_resource upstream;
    stackext_resource resource{&upstream};
    REQUIRE(resource.allocate(4, 4) != nullptr);
    REQUIRE(resource.allocate(capacity + 1, 4) != nullptr);
    REQUIRE(stack_extension::size() == 4);
    REQUIRE(upstream.count() > capacity);
    resource.release();
    REQUIRE(stack_extension::size() == 0);
    REQUIRE(upstream.count() == 0);
  }
}
