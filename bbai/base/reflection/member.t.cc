#include "bbai/base/reflection/member.h"

#include <iostream>
#include <tuple>
#include <type_traits>

#include "bbai/base/test/unit_test.h"
using namespace bbai;
using namespace bbai::basrf;

struct my_class {
  BBAI_REFLECT_MEMBER(x, int);
  BBAI_REFLECT_MEMBER(t, std::tuple<char, float>);
};

TEST_CASE("we can reflect the members of a class") {
  static constexpr size_t num_members = num_members_v<my_class>;
  REQUIRE(num_members == 2);

  static constexpr auto name1 = member_name_v<my_class, 1>;
  REQUIRE(std::string{name1} == "t");

  using t1 = member_type_t<my_class, 1>;
  REQUIRE(std::is_same_v<t1, std::tuple<char, float>>);
}
