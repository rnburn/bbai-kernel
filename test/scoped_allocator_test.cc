#include "stackext/scoped_allocator.h"

#include "3rd_party/catch2/catch.hpp"

TEST_CASE(
    "scoped_allocator allocates memory that's freed when the scope exits.") {
  stackext::stack_allocator base_allocator{100};

  SECTION("memory is freed upon scope exit.") {
    {
      stackext::scoped_allocator allocator{base_allocator};
      REQUIRE(allocator.allocate<4>(10) != nullptr);
      REQUIRE(base_allocator.size() == 10);
    }
    REQUIRE(base_allocator.size() == 0);
  }

  SECTION(
      "if enough memory isn't available from the base_allocator, it's taken "
      "from the heap.") {
    stackext::scoped_allocator allocator{base_allocator};
    REQUIRE(allocator.allocate<4>(101) != nullptr);
    REQUIRE(base_allocator.size() == 0);
    REQUIRE(allocator.allocate<4>(110) != nullptr);
    REQUIRE(base_allocator.size() == 0);
  }

  SECTION("we can allocate classes with trivial constructors.") {
    struct A {};
    stackext::scoped_allocator allocator{base_allocator};
    auto ptr = allocator.allocate<A>(2);
    REQUIRE(base_allocator.size() == sizeof(A) * 2);
  }

  SECTION("we can allocate classes with non-trivial constructors.") {
    struct A {
      int x{92};
    };
    stackext::scoped_allocator allocator{base_allocator};
    auto ptr = allocator.allocate<A>(2);
    REQUIRE(ptr[0].x == 92);
    REQUIRE(ptr[1].x == 92);
  }

  SECTION("we can pass arguments to constructors when classes are allocated.") {
    struct A {
      int x;

      A(int xx) noexcept : x{xx} {}
    };
    stackext::scoped_allocator allocator{base_allocator};
    auto ptr = allocator.allocate<A>(2, 32);
    REQUIRE(ptr[0].x == 32);
    REQUIRE(ptr[1].x == 32);
  }

  SECTION("non-trivial destructors are called upon scope exit.") {
    class A {
     public:
      A(int& counter) noexcept : counter_{counter} {}

      ~A() noexcept { ++counter_; }

     private:
      int& counter_;
    };

    int counter{0};
    {
      stackext::scoped_allocator allocator{base_allocator};
      allocator.allocate<A>(2, counter);
      allocator.allocate<A>(3, counter);
      allocator.allocate<A>(10, counter);
      allocator.allocate<A>(11, counter);
    }
    REQUIRE(counter == 26);
  }

  SECTION("objects are destroyed in the reverse order from allocation.") {
    struct A {
      std::string& s;
      char c;

      A(std::string& ss, char cc) noexcept : s{ss}, c{cc} {}

      ~A() { s += c; }
    };

    std::string s;
    {
      stackext::scoped_allocator allocator{base_allocator};
      allocator.allocate<A>(1, s, 'A');
      allocator.allocate<A>(1, s, 'B');
    }
    REQUIRE(s == "BA");
  };
}
