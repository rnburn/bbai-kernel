#include "stackext/scoped_allocator.h"

#include "3rd_party/catch2/catch.hpp"

struct TrivialClass {
};

struct NonTrivialClass1 {
  int x{92};
};

struct NonTrivialClass2 {
  int x;

  NonTrivialClass2(int xx) noexcept : x{xx} {}
};

class NonTrivialClass3 {
 public:
  NonTrivialClass3(int& counter) noexcept : counter_{counter} {}

  ~NonTrivialClass3() noexcept { ++counter_; }

 private:
  int& counter_;
};

TEST_CASE("scoped_allocator allocates memory that's freed when the scope exits.") {
  stackext::linear_allocator base_allocator{100};

  SECTION("memory is freed upon scope exit.") {
    {
      stackext::scoped_allocator allocator{base_allocator};
      REQUIRE(allocator.allocate<4>(10) != nullptr);
      REQUIRE(base_allocator.size() == 10);
    }
    REQUIRE(base_allocator.size() == 0);
  }

  SECTION("if enough memory isn't available from the base_allocator, it's taken from the heap.") {
    stackext::scoped_allocator allocator{base_allocator};
    REQUIRE(allocator.allocate<4>(101) != nullptr);
    REQUIRE(base_allocator.size() == 0);
    REQUIRE(allocator.allocate<4>(110) != nullptr);
    REQUIRE(base_allocator.size() == 0);
  }

  SECTION("we can allocate classes with trivial constructors.") {
    stackext::scoped_allocator allocator{base_allocator};
    auto ptr = allocator.allocate<TrivialClass>(2);
    REQUIRE(base_allocator.size() == sizeof(TrivialClass)*2);
  }

  SECTION("we can allocate classes with non-trivial constructors.") {
    stackext::scoped_allocator allocator{base_allocator};
    auto ptr = allocator.allocate<NonTrivialClass1>(2);
    REQUIRE(ptr[0].x == 92);
    REQUIRE(ptr[1].x == 92);
  }

  SECTION("we can pass arguments to constructors when classes are allocated.") {
    stackext::scoped_allocator allocator{base_allocator};
    auto ptr = allocator.allocate<NonTrivialClass2>(2, 32);
    REQUIRE(ptr[0].x == 32);
    REQUIRE(ptr[1].x == 32);
  }

  SECTION("non-trivial destructors are called upon scope exit.") {
    int counter{0};
    {
      stackext::scoped_allocator allocator{base_allocator};
      allocator.allocate<NonTrivialClass3>(2, counter);
      allocator.allocate<NonTrivialClass3>(3, counter);
    }
    REQUIRE(counter == 5);
  }
}
