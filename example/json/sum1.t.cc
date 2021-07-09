#include "sum1.h"

#include <string_view>

#include "parse_json1.h"

#include "bbai/base/test/unit_test.h"
#include "bbai/memory/management/managed_ptr.h"
using namespace bbai;
using namespace bbai::jsonex;

TEST_CASE("we can sum over parsed json") {
  memmg::managed_ptr<json_value> json;

  SECTION("we can sum empty json") {
    std::string_view s = "";
    parse_json(json, s);
    REQUIRE(sum1(json.get()) == 0);
  }

  SECTION("verify sum") {
    std::string_view s = "[0, 3, [-1, 10]]";
    parse_json(json, s);
    REQUIRE(sum1(json.get()) == 12);
  }
}
