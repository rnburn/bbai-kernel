#include "parse_number.h"

#include <cctype>
#include <charconv>

#include "json_parse_error.h"

namespace bbai::jsonex {
//--------------------------------------------------------------------------------------------------
// is_number_leading_char
//--------------------------------------------------------------------------------------------------
bool is_number_leading_char(char c) noexcept {
  return std::isdigit(c) != 0 || c == '-';
}

//--------------------------------------------------------------------------------------------------
// parse_number
//--------------------------------------------------------------------------------------------------
int parse_number(std::string_view& s) {
  int x;
  auto [ptr, ec] = std::from_chars(s.begin(), s.end(), x);
  if (ec != std::errc{}) {
    throw json_parse_error{};
  }
  s = std::string_view{ptr, s.end()};
  return x;
}
} // namespace bbai::jsonex
