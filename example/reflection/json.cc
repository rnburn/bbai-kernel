#include <iostream>
#include <type_traits>
#include <utility>
#include <vector>

#include "bbai/base/reflection/member.h"
using namespace bbai;

template <class T>
  requires std::is_integral_v<T>
void print_json(std::ostream& out, T x) noexcept {
  out << x;
}

template <class T>
void print_json(std::ostream& out, const std::vector<T>& v) noexcept {
  out << "[";
  for (auto& val : v) {
    print_json(out, val);
    if (&val != &v.back()) {
      out << ",";
    }
  }
  out << "]";
}

namespace detail {
template <size_t I, size_t N, class T>
void print_json_member(std::ostream& out, const T& x) noexcept {
  constexpr auto name = basrf::member_name_v<T, I>;
  out << "\"" << std::string_view{name} << "\":";
  print_json(out, basrf::member_get<I>(x));
  if (I < N - 1) {
    out << ",";
  }
}

template <class T, size_t... Indexes>
void print_json_impl(std::ostream& out, const T& x,
                     std::index_sequence<Indexes...>) noexcept {
  constexpr auto N = sizeof...(Indexes);
  out << "{";
  (print_json_member<Indexes, N>(out, x), ...);
  out << "}";
}
} // namespace detail

template <class T>
  requires (std::is_aggregate_v<T> && basrf::num_members_v<T> > 0)
void print_json(std::ostream& out, const T& x) noexcept {
    detail::print_json_impl(
        out, x, std::make_index_sequence<basrf::num_members_v<T>>{});
}

struct employee {
  BBAI_REFLECT_MEMBER(id, int);
  BBAI_REFLECT_MEMBER(salary, int);
};

struct team {
  BBAI_REFLECT_MEMBER(id, int);
  BBAI_REFLECT_MEMBER(members, std::vector<employee>);
};

int main() {
  print_json(std::cout, 123);
  std::cout << "\n";
  std::vector<int> v = {1, 2, 3};
  print_json(std::cout, v);
  team team{
      .id = 0,
      .members =
          {
              {
                  .id = 1,
                  .salary = 100'000,
              },
              {
                  .id = 2,
                  .salary = 150'000,
              },
          },
  };
  std::cout << "\n";

  print_json(std::cout, team);
  std::cout << "\n";
  return 0;
}
