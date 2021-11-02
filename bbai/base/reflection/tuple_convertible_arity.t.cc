#include "bbai/base/reflection/tuple_convertible_arity.h"

#include <variant>

#include "bbai/base/test/unit_test.h"
using namespace bbai;
using namespace bbai::basrf;

struct a0 {};

struct a1 {
  double x1;
};

struct a2 {
  double x1;
  int x2;
};

struct a3 {
  double x1;
  int x2;
  a1 x3;
};

struct a4 {
  char x1;
  char x2;
  char x3;
  char x4;
};

struct v1 {
  std::variant<int> x;
};

TEST_CASE("we can determine the tuple_convertible_arity of a structure") {
  SECTION("Gjxd", "verify against precomputed values") {
    REQUIRE(tuple_convertible_arity_v<a0> == 0);
    REQUIRE(tuple_convertible_arity_v<a1> == 1);
    REQUIRE(tuple_convertible_arity_v<a2> == 2);
    REQUIRE(tuple_convertible_arity_v<a3> == 3);
    REQUIRE(tuple_convertible_arity_v<a4> == 4);
  }

  SECTION("3AYg", "tuple_convertible_arity_v works with variant members") {
    REQUIRE(tuple_convertible_arity_v<v1> == 1);
  }
}
