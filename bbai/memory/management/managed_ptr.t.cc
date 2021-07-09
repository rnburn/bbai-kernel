#include "bbai/memory/management/managed_ptr.h"

#include <memory_resource>
#include <vector>

#include "bbai/base/test/unit_test.h"
using namespace bbai;
using namespace bbai::memmg;

class A {
 public:
  virtual ~A() noexcept = default;

  virtual int f() const noexcept = 0;
};

class B : public A {
 public:
  explicit B(int xx) noexcept : x{xx} {}

  int x;

  int f() const noexcept override { return x; }
};

class C {
  public:
    virtual ~C() noexcept = default;

    virtual int f() const noexcept = 0;
};

class D : public A, public C {
 public:
  explicit D(int xx) noexcept : x{xx} {}

  int x;

  int f() const noexcept override { return x; }
};

class E final : public A {
 public:
  explicit E(int xx) noexcept : x{xx} {}

  int x;

  int f() const noexcept override { return x; }
};

TEST_CASE("manage_ptr is an allocate-aware smart pointer") {
  std::pmr::polymorphic_allocator<> alloc;

  std::array<char, 1000> buffer;
  std::pmr::monotonic_buffer_resource buffer_resource{
      static_cast<void*>(buffer.data()), buffer.size()};
  std::pmr::polymorphic_allocator<> alloc_p{&buffer_resource};

  SECTION("when allocators are compatible, we move from manged_ptr") {
    auto ptr = alloc.new_object<int>(123);
    managed_ptr<int> ptr1{ptr};
    managed_ptr<int> ptr2{std::move(ptr1)};
    REQUIRE(ptr1 == nullptr);
    REQUIRE(*ptr2 == 123);
    REQUIRE(ptr2.get() == ptr);
  }

  SECTION("we can construct from a const ptr") {
    auto ptr = alloc.new_object<int>(123);
    managed_ptr<const int> ptr1{ptr};
    managed_ptr<const int> ptr2{std::move(ptr1)};
    REQUIRE(ptr2.get() == ptr);
  }

  SECTION("when allocators are incompatible, we copy from manged_ptr") {
    auto ptr = alloc.new_object<int>(123);
    managed_ptr<int> ptr1{ptr};
    managed_ptr<int> ptr2{std::move(ptr1), alloc_p};
    REQUIRE(ptr1 == nullptr);
    REQUIRE(*ptr2 == 123);
    REQUIRE(ptr1.get() != ptr);
  }

  SECTION("we can use managed_ptr within an allocator-aware container") {
    std::pmr::vector<managed_ptr<A>> v{alloc_p};
    auto ptr = alloc.new_object<B>(123);
    v.emplace_back(managed_ptr<B>{ptr});
    REQUIRE(v[0]->f() == 123);
    char* vptr = reinterpret_cast<char*>(v.data());
    REQUIRE(buffer.data() <= vptr);
    REQUIRE(vptr <= buffer.data() + buffer.size());
  }

  SECTION("we can manage a pointer to classes with multiple bases") {
    auto ptr = alloc.new_object<D>(123);
    managed_ptr<C> ptr1{ptr};
    managed_ptr<C> ptr2{std::move(ptr1), alloc_p};
    REQUIRE(ptr1 == nullptr);
    REQUIRE(ptr2.get() != ptr);
    REQUIRE(ptr2->f() == 123);
  }

  SECTION("we support managed_ptr<void>") {
    managed_ptr<void> ptr1{alloc.new_object<int>(123)};
    managed_ptr<void> ptr2{std::move(ptr1)};
    REQUIRE(*static_cast<int*>(ptr2.get()) == 123);
  }

  SECTION("we can construct managed pointers to finalized classes") {
    auto ptr = alloc.new_object<E>(123);
    managed_ptr<E> ptr1{ptr};
    managed_ptr<A> ptr2{std::move(ptr1)};
    REQUIRE(ptr2.get() == ptr);
    REQUIRE(sizeof(ptr1) < sizeof(ptr2));
    REQUIRE(ptr2->f() == 123);
  }

  SECTION("we can compare managed ptrs") {
    managed_ptr<int> ptr1{alloc.new_object<int>(123)};
    managed_ptr<const int> ptr2{alloc.new_object<int>(123)};
    REQUIRE(ptr1 == ptr1);
    REQUIRE(!(ptr1 < ptr1));
    REQUIRE(ptr1 != nullptr);
    REQUIRE(ptr1 != ptr2);
  }

  SECTION("we can construct manged_ptr from nullptr") {
    managed_ptr<int> ptr1{nullptr};
    REQUIRE(ptr1 == nullptr);
  }
}
