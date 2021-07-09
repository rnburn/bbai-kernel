#pragma once

#include <string_view>

#include "bbai/memory/management/managed_ptr.h"

#include "json_value.h"

namespace bbai::jsonex {
//--------------------------------------------------------------------------------------------------
// parse_json
//--------------------------------------------------------------------------------------------------
void parse_json(memmg::managed_ptr<json_value>& json, std::string_view s);
}  // namespace bbai::jsonex
