#include "bbai/base/memory/allocator_aware_helper.h"

#include <map>
#include <memory_resource>
#include <string>
#include <string_view>
#include <vector>

#include "bbai/base/test/unit_test.h"
using namespace bbai;
using namespace bbai::basm;

struct my_data {
  std::pmr::vector<int> v_;
  int x_;
  std::pmr::map<std::pmr::string, std::pmr::string> m_;
};

class my_class final : public allocator_aware_helper<my_data> {
  public:
    using allocator_aware_helper<my_data>::allocator_aware_helper;

    void store(std::pmr::string k, std::pmr::string v) noexcept {
      m_[k] = v;
    }

    const std::pmr::string& lookup(std::pmr::string k) noexcept {
      return m_[k];
    }
};

TEST_CASE("we can easily construct allocator aware clases") {
  std::pmr::monotonic_buffer_resource resource1;
  std::pmr::monotonic_buffer_resource resource2;

  SECTION("Tt7z", "we can use my_class with custom allocators") {
    my_class mc{&resource1};
    REQUIRE(mc.get_allocator() == std::pmr::polymorphic_allocator<>{&resource1});
    mc.store("abc", "123");
    auto& s = mc.lookup("abc");
    REQUIRE(s.get_allocator() == std::pmr::polymorphic_allocator<>{&resource1});
  }

  SECTION("0stR", "we properly handle unequal allocators") {
    my_class mc1{&resource1};
    mc1.store("abc", "123");
    my_class mc2{mc1, &resource2};
    REQUIRE(mc2.get_allocator() == std::pmr::polymorphic_allocator<>{&resource2});
  }
}
