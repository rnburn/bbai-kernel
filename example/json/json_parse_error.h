#pragma once

#include <exception>

namespace bbai::jsonex {
//--------------------------------------------------------------------------------------------------
// json_parse_error
//--------------------------------------------------------------------------------------------------
class json_parse_error : public std::exception {};
} // namespace bbai::jsonex

