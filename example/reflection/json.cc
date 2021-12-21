#include <iostream>
#include <string>
#include <string_view>
#include <type_traits>
#include <utility>
#include <vector>

#include "bbai/base/reflection/member.h"
using namespace bbai;

template <class T>
requires std::is_integral_v<T>
void print_json(std::ostream& out, T x) noexcept { out << x; }

void print_json(std::ostream& out, std::string_view s) noexcept {
  // Note: for a real implementation, we'd need to escape characters like "
  // in s. But we're not going to worry about that for this example.
  out << "\"" << s << "\"";
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
  print_json(out, name);
  out << ":";
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
}  // namespace detail

template <class T>
requires(std::is_aggregate_v<T>&& basrf::num_members_v<T> >
         0) void print_json(std::ostream& out, const T& x) noexcept {
  detail::print_json_impl(out, x,
                          std::make_index_sequence<basrf::num_members_v<T>>{});
}

struct employee {
  BBAI_REFLECT_MEMBER(name, std::string);
  BBAI_REFLECT_MEMBER(salary, int);
};

struct team {
  BBAI_REFLECT_MEMBER(department, std::string);
  BBAI_REFLECT_MEMBER(employees, std::vector<employee>);
};

struct company {
  BBAI_REFLECT_MEMBER(name, std::string);
  BBAI_REFLECT_MEMBER(teams, std::vector<team>);
};

int main() {
  company company{
      .name{"Acme"},
      .teams{
          {
              .department{"sales"},
              .employees{
                  {
                      .name{"Daffy"},
                      .salary{70'000},
                  },
                  {
                      .name{"Dot"},
                      .salary{125'000},
                  },
              },
          },
          {
              .department{"engineering"},
              .employees{
                  {.name{"Wakko"}, .salary{100'000}},
              },
          },
      },
  };
  print_json(std::cout, company);
  std::cout << "\n";
  return 0;
}
