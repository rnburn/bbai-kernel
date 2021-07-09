#include "parse_json1.h"

#include "bbai/memory/resource/stackext_resource.h"
#include "bbai/base/test/unit_test.h"
using namespace bbai;
using namespace bbai::jsonex;

TEST_CASE("we can parse json") {
  memmg::managed_ptr<json_value> json;

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

  SECTION("we can parse into a custom allocator") {
    memr::stackext_resource resource;
    memmg::managed_ptr<json_value> json_p{&resource};
    std::string s = "[1,[],[2,3]]";
    parse_json(json_p, s);
    REQUIRE(json_p != nullptr);
    REQUIRE(json_p->to_string() == s);
    json = std::move(json_p);
    REQUIRE(json->to_string() == s);
  }

  SECTION("we can wink out") {
    memr::stackext_resource resource;
    std::pmr::polymorphic_allocator<> alloc{&resource};
    auto json_p = alloc.new_object<memmg::managed_ptr<json_value>>();
    std::string s = "[1,[],[2,3]]";
    parse_json(*json_p, s);
    REQUIRE(*json_p != nullptr);
    REQUIRE((*json_p)->to_string() == s);
  }
}
