# bbai-mem

![](https://github.com/rnburn/bbai-mem/workflows/pr-build-test/badge.svg) [![License](https://img.shields.io/badge/License-Apache%202.0-blue.svg)](https://opensource.org/licenses/Apache-2.0)

bbai-mem extends C++17 polymorphic allocators with
* An allocator aware smart pointer
* A resource for allocating from extended stack space

## Documentaation
* [How to Build an Allocator-aware Smart Pointer](https://buildingblock.ai/allocator-aware-smart-ptr)
* [How to Make Your C++ Code Faster With Extended Stack Space](https://buildingblock.ai/extended-stack)

## Quick start

```cpp
#include <array>
#include <cassert>
#include <iostream>
#include <memory_resource>

#include "bbai/memory/management/managed_ptr.h"
#include "bbai/memory/management/managed_ptr_utility.h"

struct A {
  virtual ~A() noexcept = default;

  virtual int f() const noexcept = 0;
};

struct B final : public A {
  explicit B(int xx) : x{xx} {}
  int x;

  int f() const noexcept override { return x; }
};

int main() {
  std::array<char, 100> buffer;
  std::pmr::monotonic_buffer_resource resource{static_cast<void*>(buffer.data()),
                                               buffer.size()};

  bbai::memmg::managed_ptr<A> ptr1{&resource};
    // we configure ptr1 to allocate into buffer

  std::pmr::polymorphic_allocator<> alloc;
  bbai::memmg::managed_ptr<A> ptr2 = bbai::memmg::allocate_managed<B>(alloc, 123);
    // ptr2 manages memory from the heap

  ptr1 = std::move(ptr2); 
    // because the two pointers have unequal allocators, the assignment will
    // reallocate and moveconstruct a B type into the buffer

  std::cout << (reinterpret_cast<char*>(ptr1.get()) == buffer.data()) << "\n"; // prints 1
  std::cout << ptr1->f() << std::endl; // prints 123

  return 0;
}
```
