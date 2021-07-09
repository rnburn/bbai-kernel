#include "whitespace.h"

#include <cctype>

namespace bbai::jsonex {
//--------------------------------------------------------------------------------------------------
// consume_whitespace
//--------------------------------------------------------------------------------------------------
void consume_whitespace(std::string_view& s) noexcept {
  auto iter = s.begin();
  for(; iter!=s.end(); ++iter) {
    if (std::isspace(*iter) == 0) {
      break;
    }
  }
  s = std::string_view{iter, s.end()};
}
} // namespace bbai::jsonex
