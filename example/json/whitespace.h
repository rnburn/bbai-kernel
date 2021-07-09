#pragma once

#include <string_view>

namespace bbai::jsonex {
//--------------------------------------------------------------------------------------------------
// consume_whitespace
//--------------------------------------------------------------------------------------------------
void consume_whitespace(std::string_view& s) noexcept;
} // namespace bbai::jsonex
