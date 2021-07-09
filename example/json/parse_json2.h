#pragma once

#include <memory>
#include <string_view>

#include "json_value.h"

namespace bbai::jsonex {
//--------------------------------------------------------------------------------------------------
// parse_json
//--------------------------------------------------------------------------------------------------
void parse_json(std::unique_ptr<json_value>& json, std::string_view s);
}  // namespace bbai::jsonex
