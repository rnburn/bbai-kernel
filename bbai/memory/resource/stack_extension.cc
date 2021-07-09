#include "bbai/memory/resource/stack_extension.h"

#include "bbai/memory/resource/stack.h"

#ifndef BBAI_EXT_STACK_SIZE 
#define BBAI_EXT_STACK_SIZE (1ull << 21)
#endif

namespace bbai::memr {
//--------------------------------------------------------------------------------------------------
// stack_extension_size_v
//--------------------------------------------------------------------------------------------------
static constexpr size_t stack_extension_size_v = BBAI_EXT_STACK_SIZE;

//--------------------------------------------------------------------------------------------------
// stack_extension_v
//--------------------------------------------------------------------------------------------------
static thread_local constinit stack<stack_extension_size_v> stack_extension_v{};

//--------------------------------------------------------------------------------------------------
// capacity
//--------------------------------------------------------------------------------------------------
size_t stack_extension::capacity() noexcept {
  return stack_extension_v.capacity();
}

//--------------------------------------------------------------------------------------------------
// size
//--------------------------------------------------------------------------------------------------
size_t stack_extension::size() noexcept {
  return stack_extension_v.size();
}

//--------------------------------------------------------------------------------------------------
// top
//--------------------------------------------------------------------------------------------------
void* stack_extension::top() noexcept {
  return stack_extension_v.top();
}

//--------------------------------------------------------------------------------------------------
// allocate
//--------------------------------------------------------------------------------------------------
void* stack_extension::allocate(size_t num_bytes) noexcept {
  return stack_extension_v.allocate(num_bytes);
}

//--------------------------------------------------------------------------------------------------
// deallocate
//--------------------------------------------------------------------------------------------------
void stack_extension::deallocate(size_t num_bytes) noexcept {
  return stack_extension_v.deallocate(num_bytes);
}
} // namespace bbai::memr
