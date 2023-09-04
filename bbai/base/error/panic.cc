#include "bbai/base/error/panic.h"

#include <cstdio>
#include <cstdlib>

namespace bbai::baser {
//--------------------------------------------------------------------------------------------------
// panic_impl
//--------------------------------------------------------------------------------------------------
[[noreturn]] void panic_impl(const char* s) noexcept {
  std::fputs(s, stderr);
  std::abort();
}
} // namespace bbai
