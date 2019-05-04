#include "stackext/utility.h"

#include <stdexcept>

#include "3rd_party/catch2/catch.hpp"

struct A {
  int x{9};
};

class B {
  public:
    B(int& construct_counter, int& destruct_counter)
      : construct_counter_{construct_counter}, destruct_counter_{destruct_counter}
    {
      ++construct_counter_;
      if (construct_counter_ == 3) {
        throw std::runtime_error{""};
      }
    }

    ~B() noexcept {
      ++destruct_counter_;
    }
  private:
    int& construct_counter_;
    int& destruct_counter_;
};

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

TEST_CASE("construct constructs a range of objects in place.") {
  int data[2];
  auto ptr = reinterpret_cast<A*>(data);
  stackext::construct(ptr, ptr+2);
  REQUIRE(ptr->x == 9);
  ++ptr;
  REQUIRE(ptr->x == 9);
}

TEST_CASE("construct propery destructs objects if an exception is thrown.") {
  alignas(B) char data[sizeof(B)*10];
  auto ptr = reinterpret_cast<B*>(data);
  int construct_counter = 0;
  int destruct_counter = 0;
  REQUIRE_THROWS(stackext::construct(ptr, ptr+10, construct_counter, destruct_counter));
  REQUIRE(construct_counter == 3);
  REQUIRE(destruct_counter == 2);
}
