#pragma once

#include <cstddef>
#include <type_traits>

#include "bbai/base/type/uncvref.h"

namespace bbai::basrf {
//--------------------------------------------------------------------------------------------------
// is_aggregate_initializable_n
//--------------------------------------------------------------------------------------------------
namespace detail {
template <class, size_t>
struct is_aggregate_initializable_n_impl {
  static constexpr bool value = false;
};

template<class T>
  requires requires {
    T{};
  }
struct is_aggregate_initializable_n_impl<T, 0> {
  static constexpr bool value = true;
};

template <class T>
  requires requires {
    T{{}};
  }
struct is_aggregate_initializable_n_impl<T, 1> {
  static constexpr bool value = true;
};

template <class T>
  requires requires {
    T{{}, {}};
  }
struct is_aggregate_initializable_n_impl<T, 2> {
  static constexpr bool value = true;
};

template <class T>
  requires requires {
    T{{}, {}, {}};
  }
struct is_aggregate_initializable_n_impl<T, 3> {
  static constexpr bool value = true;
};

template <class T>
  requires requires {
    T{{}, {}, {}, {}};
  }
struct is_aggregate_initializable_n_impl<T, 4> {
  static constexpr bool value = true;
};

template <class T>
  requires requires {
    T{{}, {}, {}, {}, {}};
  }
struct is_aggregate_initializable_n_impl<T, 5> {
  static constexpr bool value = true;
};

template <class T>
  requires requires {
    T{{}, {}, {}, {}, {}, {}};
  }
struct is_aggregate_initializable_n_impl<T, 6> {
  static constexpr bool value = true;
};

template <class T>
  requires requires {
    T{{}, {}, {}, {}, {}, {}, {}};
  }
struct is_aggregate_initializable_n_impl<T, 7> {
  static constexpr bool value = true;
};

template <class T>
  requires requires {
    T{{}, {}, {}, {}, {}, {}, {}, {}};
  }
struct is_aggregate_initializable_n_impl<T, 8> {
  static constexpr bool value = true;
};

template <class T>
  requires requires {
    T{{}, {}, {}, {}, {}, {}, {}, {}, {}};
  }
struct is_aggregate_initializable_n_impl<T, 9> {
  static constexpr bool value = true;
};

template <class T>
  requires requires {
    T{{}, {}, {}, {}, {}, {}, {}, {}, {}, {}};
  }
struct is_aggregate_initializable_n_impl<T, 10> {
  static constexpr bool value = true;
};

template <class T>
  requires requires {
    T{{}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}};
  }
struct is_aggregate_initializable_n_impl<T, 11> {
  static constexpr bool value = true;
};

template <class T>
  requires requires {
    T{{}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}};
  }
struct is_aggregate_initializable_n_impl<T, 12> {
  static constexpr bool value = true;
};

template <class T>
  requires requires {
    T{{}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}};
  }
struct is_aggregate_initializable_n_impl<T, 13> {
  static constexpr bool value = true;
};

template <class T>
  requires requires {
    T{{}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}};
  }
struct is_aggregate_initializable_n_impl<T, 14> {
  static constexpr bool value = true;
};

template <class T>
  requires requires {
    T{{}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}};
  }
struct is_aggregate_initializable_n_impl<T, 15> {
  static constexpr bool value = true;
};

template <class T>
  requires requires {
    T{{}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}};
  }
struct is_aggregate_initializable_n_impl<T, 16> {
  static constexpr bool value = true;
};

template <class T>
  requires requires {
    T{{}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}};
  }
struct is_aggregate_initializable_n_impl<T, 17> {
  static constexpr bool value = true;
};

template <class T>
  requires requires {
    T{{}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}};
  }
struct is_aggregate_initializable_n_impl<T, 18> {
  static constexpr bool value = true;
};

template <class T>
  requires requires {
    T{{}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}};
  }
struct is_aggregate_initializable_n_impl<T, 19> {
  static constexpr bool value = true;
};

template <class T>
  requires requires {
    T{{}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}};
  }
struct is_aggregate_initializable_n_impl<T, 20> {
  static constexpr bool value = true;
};

template <class T>
  requires requires {
    T{{}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}};
  }
struct is_aggregate_initializable_n_impl<T, 21> {
  static constexpr bool value = true;
};

template <class T>
  requires requires {
    T{{}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}};
  }
struct is_aggregate_initializable_n_impl<T, 22> {
  static constexpr bool value = true;
};

template <class T>
  requires requires {
    T{{}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}};
  }
struct is_aggregate_initializable_n_impl<T, 23> {
  static constexpr bool value = true;
};

template <class T>
  requires requires {
    T{{}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}};
  }
struct is_aggregate_initializable_n_impl<T, 24> {
  static constexpr bool value = true;
};

template <class T>
  requires requires {
    T{{}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}};
  }
struct is_aggregate_initializable_n_impl<T, 25> {
  static constexpr bool value = true;
};

template <class T>
  requires requires {
    T{{}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}};
  }
struct is_aggregate_initializable_n_impl<T, 26> {
  static constexpr bool value = true;
};

template <class T>
  requires requires {
    T{{}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}};
  }
struct is_aggregate_initializable_n_impl<T, 27> {
  static constexpr bool value = true;
};

template <class T>
  requires requires {
    T{{}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}};
  }
struct is_aggregate_initializable_n_impl<T, 28> {
  static constexpr bool value = true;
};

template <class T>
  requires requires {
    T{{}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}};
  }
struct is_aggregate_initializable_n_impl<T, 29> {
  static constexpr bool value = true;
};

template <class T>
  requires requires {
    T{{}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}};
  }
struct is_aggregate_initializable_n_impl<T, 30> {
  static constexpr bool value = true;
};

template <class T>
  requires requires {
    T{{}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}};
  }
struct is_aggregate_initializable_n_impl<T, 31> {
  static constexpr bool value = true;
};

template <class T>
  requires requires {
    T{{}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}};
  }
struct is_aggregate_initializable_n_impl<T, 32> {
  static constexpr bool value = true;
};

template <class T>
  requires requires {
    T{{}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}};
  }
struct is_aggregate_initializable_n_impl<T, 33> {
  static constexpr bool value = true;
};

template <class T>
  requires requires {
    T{{}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}};
  }
struct is_aggregate_initializable_n_impl<T, 34> {
  static constexpr bool value = true;
};

template <class T>
  requires requires {
    T{{}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}};
  }
struct is_aggregate_initializable_n_impl<T, 35> {
  static constexpr bool value = true;
};

template <class T>
  requires requires {
    T{{}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}};
  }
struct is_aggregate_initializable_n_impl<T, 36> {
  static constexpr bool value = true;
};

template <class T>
  requires requires {
    T{{}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}};
  }
struct is_aggregate_initializable_n_impl<T, 37> {
  static constexpr bool value = true;
};

template <class T>
  requires requires {
    T{{}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}};
  }
struct is_aggregate_initializable_n_impl<T, 38> {
  static constexpr bool value = true;
};

template <class T>
  requires requires {
    T{{}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}};
  }
struct is_aggregate_initializable_n_impl<T, 39> {
  static constexpr bool value = true;
};

template <class T>
  requires requires {
    T{{}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}};
  }
struct is_aggregate_initializable_n_impl<T, 40> {
  static constexpr bool value = true;
};

template <class T>
  requires requires {
    T{{}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}};
  }
struct is_aggregate_initializable_n_impl<T, 41> {
  static constexpr bool value = true;
};

template <class T>
  requires requires {
    T{{}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}};
  }
struct is_aggregate_initializable_n_impl<T, 42> {
  static constexpr bool value = true;
};

template <class T>
  requires requires {
    T{{}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}};
  }
struct is_aggregate_initializable_n_impl<T, 43> {
  static constexpr bool value = true;
};

template <class T>
  requires requires {
    T{{}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}};
  }
struct is_aggregate_initializable_n_impl<T, 44> {
  static constexpr bool value = true;
};

template <class T>
  requires requires {
    T{{}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}};
  }
struct is_aggregate_initializable_n_impl<T, 45> {
  static constexpr bool value = true;
};

template <class T>
  requires requires {
    T{{}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}};
  }
struct is_aggregate_initializable_n_impl<T, 46> {
  static constexpr bool value = true;
};

template <class T>
  requires requires {
    T{{}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}};
  }
struct is_aggregate_initializable_n_impl<T, 47> {
  static constexpr bool value = true;
};

template <class T>
  requires requires {
    T{{}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}};
  }
struct is_aggregate_initializable_n_impl<T, 48> {
  static constexpr bool value = true;
};

template <class T>
  requires requires {
    T{{}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}};
  }
struct is_aggregate_initializable_n_impl<T, 49> {
  static constexpr bool value = true;
};

template <class T>
  requires requires {
    T{{}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}};
  }
struct is_aggregate_initializable_n_impl<T, 50> {
  static constexpr bool value = true;
};

template <class T, size_t N>
  requires (N > 50) && requires {
    T{{}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}};
  }
struct is_aggregate_initializable_n_impl<T, N> {
  static_assert(N != N, "arity limit exceeded");
};

template <class T, size_t N>
  requires std::is_aggregate_v<T>
constexpr bool is_aggregate_initializable_n_v =
      is_aggregate_initializable_n_impl<T, N>::value;
} // namespace detail

//--------------------------------------------------------------------------------------------------
// tuple_convertible_arity_v
//--------------------------------------------------------------------------------------------------
namespace detail {
template <class T, size_t I, size_t J> struct tuple_convertible_arity_impl {};

template <class T, size_t I, size_t J>
  requires (J == I + 1)
struct tuple_convertible_arity_impl<T, I, J> {
  static constexpr size_t value = I;
};

template <class T, size_t I, size_t J>
  requires (J > I + 1 && is_aggregate_initializable_n_v<T, (I + J) / 2>)
struct tuple_convertible_arity_impl<T, I, J> {
  static constexpr size_t value = tuple_convertible_arity_impl<T, (I + J)/2, J>::value;
};

template <class T, size_t I, size_t J>
  requires (J > I + 1 && !is_aggregate_initializable_n_v<T, (I + J) / 2>)
struct tuple_convertible_arity_impl<T, I, J> {
  static constexpr size_t value = tuple_convertible_arity_impl<T, I, (I + J)/2>::value;
};
} // namespace detail

template <class T>
  requires std::is_aggregate_v<bast::uncvref_t<T>>
constexpr size_t tuple_convertible_arity_v = 
  detail::tuple_convertible_arity_impl<bast::uncvref_t<T>, 0, sizeof(T)+1>::value;
} // namespace bbai::basrf
