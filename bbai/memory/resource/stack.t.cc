#include "bbai/memory/resource/stack.h"

#include "bbai/base/test/unit_test.h"
using namespace bbai;
using namespace bbai::memr;

TEST_CASE("stack manages LIFO allocations") {
  stack<100> s;

  SECTION("a stack starts empty") {
    REQUIRE(s.capacity() == 100);
    REQUIRE(s.size() == 0);
  }

  SECTION("we can allocate and deallocate from a stack") {
    size_t num_bytes = 100;
    s.allocate(num_bytes);
    REQUIRE(s.size() == num_bytes);
    s.deallocate(num_bytes);
    REQUIRE(s.size() == 0);
  }
}
