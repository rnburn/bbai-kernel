#include "parse_json2.h"

#include <cassert>

#include "json_array2.h"
#include "json_number.h"
#include "json_parse_error.h"
#include "parse_number.h"
#include "whitespace.h"

namespace bbai::jsonex {
static void parse_value(std::unique_ptr<json_value>& value, std::string_view& s);

//--------------------------------------------------------------------------------------------------
// parse_array_values
//--------------------------------------------------------------------------------------------------
static void parse_array_values(
    std::vector<std::unique_ptr<const json_value>>& values,
    std::string_view& s) {
  while (true) {
    std::unique_ptr<json_value> value;
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
static void parse_array(std::unique_ptr<json_value>& json,
                        std::string_view& s) {
  assert(!s.empty() && s[0] == '[');
  s = std::string_view{s.begin() + 1, s.end()};
  std::vector<std::unique_ptr<const json_value>> values;
  consume_whitespace(s);
  if (s.empty()) {
    throw json_parse_error{};
  }
  if (s[0] != ']') {
    parse_array_values(values, s);
  }
  s = std::string_view{s.begin() + 1, s.end()};
  json = std::make_unique<json_array2>(std::move(values));
}

//--------------------------------------------------------------------------------------------------
// parse_value
//--------------------------------------------------------------------------------------------------
void parse_value(std::unique_ptr<json_value>& json, std::string_view& s) {
  if (s.empty()) {
    throw json_parse_error{};
  }
  auto c = s[0];
  if (is_number_leading_char(c)) {
    auto  x = parse_number(s);
    json = std::make_unique<json_number>(x);
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
void parse_json(std::unique_ptr<json_value>& json,
                std::string_view s) {
  consume_whitespace(s);
  if (s.empty()) {
    return;
  }
  parse_value(json, s);
}
} // namespace bbai::jsonex
