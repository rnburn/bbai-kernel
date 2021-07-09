#include "bbai/memory/management/pointer_operator_function.h"

#include <vector>

#include "bbai/base/test/unit_test.h"
using namespace bbai;
using namespace bbai::memmg;

TEST_CASE("we can construct derived pointers through a operator function") {
  std::pmr::polymorphic_allocator<> alloc;

  std::array<char, 100> buffer;
  std::pmr::monotonic_buffer_resource buffer_resource{
      static_cast<void*>(buffer.data()), buffer.size()};
  std::pmr::polymorphic_allocator<> alloc_p{&buffer_resource};
  
  SECTION("we can construct points of the same type") {
    auto fn = pointer_operator_function_v<int>;

    int x = 123;

    int* x_p = static_cast<int*>(fn(static_cast<void*>(&x), alloc, true));
    REQUIRE(*x_p == x);
    fn(x_p, alloc, false);
  }

  SECTION("we pass the allocator through to allocator aware types") {
    using T = std::pmr::vector<int>;
    T v = {1, 2, 3};
    auto fn = pointer_operator_function_v<T>;
    auto v_p = static_cast<T*>(fn(static_cast<void*>(&v), alloc_p, true));
    REQUIRE(T{1, 2, 3} == *v_p);
    REQUIRE(v_p->get_allocator() == alloc_p);
    fn(static_cast<void*>(v_p), alloc_p, false);
  }
}
