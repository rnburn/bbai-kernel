#include "parse_json2.h"

#include "bbai/base/test/unit_test.h"
using namespace bbai;
using namespace bbai::jsonex;

TEST_CASE("we can parse json") {
  std::unique_ptr<json_value> json;

  SECTION("we can parse an empty string") {
    std::string s = "";
    parse_json(json, s);
    REQUIRE(json == nullptr);
  }

  SECTION("we can parse a single number") {
    std::string s = "123";
    parse_json(json, s);
    REQUIRE(json != nullptr);
    REQUIRE(json->to_string() == s); 
  }

  SECTION("we can parse an empty list") {
    std::string s = "[]";
    parse_json(json, s);
    REQUIRE(json != nullptr);
    REQUIRE(json->to_string() == s); 
  }

  SECTION("we can parse a list with a single entry") {
    std::string s = "[123]";
    parse_json(json, s);
    REQUIRE(json != nullptr);
    REQUIRE(json->to_string() == s); 
  }

  SECTION("we can parse a list with multiple entries") {
    std::string s = "[1,2,3]";
    parse_json(json, s);
    REQUIRE(json != nullptr);
    REQUIRE(json->to_string() == s); 
  }

  SECTION("we can parse nested lists") {
    std::string s = "[1,[],[2,3]]";
    parse_json(json, s);
    REQUIRE(json != nullptr);
    REQUIRE(json->to_string() == s); 
  }

  SECTION("we ignore whitespace") {
    std::string s = "   [1 ,  2 ,    3 ]   ";
    parse_json(json, s);
    REQUIRE(json != nullptr);
    REQUIRE(json->to_string() == "[1,2,3]"); 
  }
}
