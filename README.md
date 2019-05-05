# stackext

Small, header-only library for working with an extended stack. Like [alloca](http://man7.org/linux/man-pages/man3/alloca.3.html), stackext provides a much faster
alternative than the heap for allocating memory that doesn't need to persist beyond a function's scope. But, unlike alloca, stackext 
1. Doesn't risk causing a stack overflow. If an allocation can't fit into the extended stack, it falls back to heap allocation.
1. Works with classes that have non-trivial constructors and destructors.

## Installation

```
sudo cp -r include/stackext /usr/local/include
```

## Quick start

```cpp
// Set aside 1KB of extended stack space.
static thread_local stackext::stack_allocator ExtendedStack{1024};

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

    ~A() {
      std::cout << "~A\n";
    }
  };
  auto aptr = allocator.allocate<A>(3, 97);
  (void)aptr;

  // allocations larger than the amount of stack space reserved will fall back
  // to using the heap
  auto bigdata = allocator.allocate<char>(1024 * 1024);
  (void)bigdata;

  // we can nest usages of scoped_allocator
  example2();
}

static void example2() {
  stackext::scoped_allocator allocator{ExtendedStack};
  struct B {
    B() { std::cout << "B\n"; };
  };
  auto bptr = allocator.allocate<B>(5);
  (void)bptr;
}
```
