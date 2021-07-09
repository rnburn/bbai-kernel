#include "parse_json1.h"

#include <cassert>

#include "bbai/memory/management/managed_ptr_utility.h"

#include "json_array1.h"
#include "json_number.h"
#include "json_parse_error.h"
#include "parse_number.h"
#include "whitespace.h"

namespace bbai::jsonex {
static void parse_value(memmg::managed_ptr<json_value>& value, std::string_view& s);

//--------------------------------------------------------------------------------------------------
// parse_array_values
//--------------------------------------------------------------------------------------------------
static void parse_array_values(
    std::pmr::vector<memmg::managed_ptr<const json_value>>& values,
    std::string_view& s) {
  while (true) {
    memmg::managed_ptr<json_value> value{values.get_allocator()};
    parse_value(value, s);
    values.emplace_back(std::move(value));
    consume_whitespace(s);
    if (s.empty()) {
      throw json_parse_error{};
    }
    if (s[0] == ',') {
      s = std::string_view{s.begin() + 1, s.end()};
      consume_whitespace(s);
    } else if (s[0] == ']') {
      return;
    }
  }
}

//--------------------------------------------------------------------------------------------------
// parse_array
//--------------------------------------------------------------------------------------------------
static void parse_array(memmg::managed_ptr<json_value>& json,
                        std::string_view& s) {
  assert(!s.empty() && s[0] == '[');
  s = std::string_view{s.begin() + 1, s.end()};
  std::pmr::vector<memmg::managed_ptr<const json_value>> values{
      json.get_allocator()};
  consume_whitespace(s);
  if (s.empty()) {
    throw json_parse_error{};
  }
  if (s[0] != ']') {
    parse_array_values(values, s);
  }
  s = std::string_view{s.begin() + 1, s.end()};
  json = memmg::allocate_managed<json_array1>(json.get_allocator(),
                                                  std::move(values));
}

//--------------------------------------------------------------------------------------------------
// parse_value
//--------------------------------------------------------------------------------------------------
void parse_value(memmg::managed_ptr<json_value>& json, std::string_view& s) {
  if (s.empty()) {
    throw json_parse_error{};
  }
  auto c = s[0];
  if (is_number_leading_char(c)) {
    auto  x = parse_number(s);
    json = memmg::allocate_managed<json_number>(json.get_allocator(), x);
    return;
  } else if (c == '[') {
    parse_array(json, s);
  } else {
    throw json_parse_error{};
  }
};

//--------------------------------------------------------------------------------------------------
// parse_json
//--------------------------------------------------------------------------------------------------
void parse_json(memmg::managed_ptr<json_value>& json,
                std::string_view s) {
  consume_whitespace(s);
  if (s.empty()) {
    return;
  }
  parse_value(json, s);
}
} // namespace bbai::jsonex
