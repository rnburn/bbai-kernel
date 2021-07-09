#include "sum2.h"

#include <memory>
#include <string_view>

#include "parse_json2.h"

#include "bbai/base/test/unit_test.h"
using namespace bbai;
using namespace bbai::jsonex;

TEST_CASE("we can sum over parsed json") {
  std::unique_ptr<json_value> json;

  SECTION("we can sum empty json") {
    std::string_view s = "";
    parse_json(json, s);
    REQUIRE(sum2(json.get()) == 0);
  }

  SECTION("verify sum") {
    std::string_view s = "[0, 3, [-1, 10]]";
    parse_json(json, s);
    REQUIRE(sum2(json.get()) == 12);
  }
}
