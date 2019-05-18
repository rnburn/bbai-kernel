#include "stackext/scoped_allocator.h"
#include "stackext/linear_allocator.h"

#include <iostream>
#include <vector>

// Set aside 1KB of extended stack space per thread.
static thread_local stackext::stack_allocator ExtendedStack{1024};

static void example2();

static void example1(int n) {
  // Make an allocator for this function's scope
  stackext::scoped_allocator allocator{ExtendedStack};

  // allocate a dynamic number of characters
  // memory for s will be freed automatically when allocator's destructor is called
  auto s = allocator.allocate<char>(n);
  (void)s;

  // allocator works with classes that have non-trivial constructors and
  // destructors
  struct A {
    A(int x) { std::cout << "A: " << x << "\n"; }

    ~A() { std::cout << "~A\n"; }
  };
  auto aptr = allocator.allocate<A>(3, 97);
  (void)aptr;

  // allocations larger than the amount of stack space reserved will fall back
  // to using the heap
  auto bigdata = allocator.allocate<char>(1024 * 1024);
  (void)bigdata;

  // we can nest usages of scoped_allocator
  example2();

  // with linear_allocator, we can use scoped_allocator with standard C++ containers
  std::vector<int, stackext::linear_allocator<int>> v(stackext::linear_allocator<int>{allocator});
  v.push_back(1);
  v.push_back(2);
  v.push_back(3);
}

static void example2() {
  stackext::scoped_allocator allocator{ExtendedStack};
  struct B {
    B() { std::cout << "B\n"; };
  };
  auto bptr = allocator.allocate<B>(5);
  (void)bptr;
}

int main() {
  example1(10);
  return 0;
}
