#pragma once

#include <type_traits>
#include <tuple>

#include "bbai/base/reflection/tuple_convertible_arity.h"
#include "bbai/base/type/uncvref.h"

namespace bbai::basrf {
//--------------------------------------------------------------------------------------------------
// as_tuple_impl
//--------------------------------------------------------------------------------------------------
namespace detail {
template <class T>
auto as_tuple_impl(T &&aggregate,
                             std::integral_constant<size_t, 0>) noexcept {
  (void)aggregate;
  return std::tuple{};
}

template <class T>
auto as_tuple_impl(T &&aggregate,
                             std::integral_constant<size_t, 1>) noexcept {
  auto &[m0] = aggregate;
  return std::forward_as_tuple(m0);
}

template <class T>
auto as_tuple_impl(T &&aggregate,
                             std::integral_constant<size_t, 2>) noexcept {
  auto &[m0, m1] = aggregate;
  return std::forward_as_tuple(m0, m1);
}

template <class T>
auto as_tuple_impl(T &&aggregate,
                             std::integral_constant<size_t, 3>) noexcept {
  auto &[m0, m1, m2] = aggregate;
  return std::forward_as_tuple(m0, m1, m2);
}

template <class T>
auto as_tuple_impl(T &&aggregate,
                             std::integral_constant<size_t, 4>) noexcept {
  auto &[m0, m1, m2, m3] = aggregate;
  return std::forward_as_tuple(m0, m1, m2, m3);
}

template <class T>
auto as_tuple_impl(T &&aggregate,
                             std::integral_constant<size_t, 5>) noexcept {
  auto &[m0, m1, m2, m3, m4] = aggregate;
  return std::forward_as_tuple(m0, m1, m2, m3, m4);
}

template <class T>
auto as_tuple_impl(T &&aggregate,
                             std::integral_constant<size_t, 6>) noexcept {
  auto &[m0, m1, m2, m3, m4, m5] = aggregate;
  return std::forward_as_tuple(m0, m1, m2, m3, m4, m5);
}

template <class T>
auto as_tuple_impl(T &&aggregate,
                             std::integral_constant<size_t, 7>) noexcept {
  auto &[m0, m1, m2, m3, m4, m5, m6] = aggregate;
  return std::forward_as_tuple(m0, m1, m2, m3, m4, m5, m6);
}

template <class T>
auto as_tuple_impl(T &&aggregate,
                             std::integral_constant<size_t, 8>) noexcept {
  auto &[m0, m1, m2, m3, m4, m5, m6, m7] = aggregate;
  return std::forward_as_tuple(m0, m1, m2, m3, m4, m5, m6, m7);
}

template <class T>
auto as_tuple_impl(T &&aggregate,
                             std::integral_constant<size_t, 9>) noexcept {
  auto &[m0, m1, m2, m3, m4, m5, m6, m7, m8] = aggregate;
  return std::forward_as_tuple(m0, m1, m2, m3, m4, m5, m6, m7, m8);
}

template <class T>
auto as_tuple_impl(T &&aggregate,
                             std::integral_constant<size_t, 10>) noexcept {
  auto &[m0, m1, m2, m3, m4, m5, m6, m7, m8, m9] = aggregate;
  return std::forward_as_tuple(m0, m1, m2, m3, m4, m5, m6, m7, m8, m9);
}

template <class T>
auto as_tuple_impl(T &&aggregate,
                             std::integral_constant<size_t, 11>) noexcept {
  auto &[m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10] = aggregate;
  return std::forward_as_tuple(m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10);
}

template <class T>
auto as_tuple_impl(T &&aggregate,
                             std::integral_constant<size_t, 12>) noexcept {
  auto &[m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11] = aggregate;
  return std::forward_as_tuple(m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10,
                               m11);
}

template <class T>
auto as_tuple_impl(T &&aggregate,
                             std::integral_constant<size_t, 13>) noexcept {
  auto &[m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11, m12] = aggregate;
  return std::forward_as_tuple(m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11,
                               m12);
}

template <class T>
auto as_tuple_impl(T &&aggregate,
                             std::integral_constant<size_t, 14>) noexcept {
  auto &[m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11, m12, m13] =
      aggregate;
  return std::forward_as_tuple(m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11,
                               m12, m13);
}

template <class T>
auto as_tuple_impl(T &&aggregate,
                             std::integral_constant<size_t, 15>) noexcept {
  auto &[m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11, m12, m13, m14] =
      aggregate;
  return std::forward_as_tuple(m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11,
                               m12, m13, m14);
}

template <class T>
auto as_tuple_impl(T &&aggregate,
                             std::integral_constant<size_t, 16>) noexcept {
  auto &[m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11, m12, m13, m14, m15] =
      aggregate;
  return std::forward_as_tuple(m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11,
                               m12, m13, m14, m15);
}

template <class T>
auto as_tuple_impl(T &&aggregate,
                             std::integral_constant<size_t, 17>) noexcept {
  auto &[m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11, m12, m13, m14, m15,
         m16] = aggregate;
  return std::forward_as_tuple(m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11,
                               m12, m13, m14, m15, m16);
}

template <class T>
auto as_tuple_impl(T &&aggregate,
                             std::integral_constant<size_t, 18>) noexcept {
  auto &[m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11, m12, m13, m14, m15,
         m16, m17] = aggregate;
  return std::forward_as_tuple(m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11,
                               m12, m13, m14, m15, m16, m17);
}

template <class T>
auto as_tuple_impl(T &&aggregate,
                             std::integral_constant<size_t, 19>) noexcept {
  auto &[m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11, m12, m13, m14, m15,
         m16, m17, m18] = aggregate;
  return std::forward_as_tuple(m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11,
                               m12, m13, m14, m15, m16, m17, m18);
}

template <class T>
auto as_tuple_impl(T &&aggregate,
                             std::integral_constant<size_t, 20>) noexcept {
  auto &[m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11, m12, m13, m14, m15,
         m16, m17, m18, m19] = aggregate;
  return std::forward_as_tuple(m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11,
                               m12, m13, m14, m15, m16, m17, m18, m19);
}

template <class T>
auto as_tuple_impl(T &&aggregate,
                             std::integral_constant<size_t, 21>) noexcept {
  auto &[m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11, m12, m13, m14, m15,
         m16, m17, m18, m19, m20] = aggregate;
  return std::forward_as_tuple(m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11,
                               m12, m13, m14, m15, m16, m17, m18, m19, m20);
}

template <class T>
auto as_tuple_impl(T &&aggregate,
                             std::integral_constant<size_t, 22>) noexcept {
  auto &[m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11, m12, m13, m14, m15,
         m16, m17, m18, m19, m20, m21] = aggregate;
  return std::forward_as_tuple(m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11,
                               m12, m13, m14, m15, m16, m17, m18, m19, m20,
                               m21);
}

template <class T>
auto as_tuple_impl(T &&aggregate,
                             std::integral_constant<size_t, 23>) noexcept {
  auto &[m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11, m12, m13, m14, m15,
         m16, m17, m18, m19, m20, m21, m22] = aggregate;
  return std::forward_as_tuple(m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11,
                               m12, m13, m14, m15, m16, m17, m18, m19, m20, m21,
                               m22);
}

template <class T>
auto as_tuple_impl(T &&aggregate,
                             std::integral_constant<size_t, 24>) noexcept {
  auto &[m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11, m12, m13, m14, m15,
         m16, m17, m18, m19, m20, m21, m22, m23] = aggregate;
  return std::forward_as_tuple(m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11,
                               m12, m13, m14, m15, m16, m17, m18, m19, m20, m21,
                               m22, m23);
}

template <class T>
auto as_tuple_impl(T &&aggregate,
                             std::integral_constant<size_t, 25>) noexcept {
  auto &[m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11, m12, m13, m14, m15,
         m16, m17, m18, m19, m20, m21, m22, m23, m24] = aggregate;
  return std::forward_as_tuple(m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11,
                               m12, m13, m14, m15, m16, m17, m18, m19, m20, m21,
                               m22, m23, m24);
}

template <class T>
auto as_tuple_impl(T &&aggregate,
                             std::integral_constant<size_t, 26>) noexcept {
  auto &[m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11, m12, m13, m14, m15,
         m16, m17, m18, m19, m20, m21, m22, m23, m24, m25] = aggregate;
  return std::forward_as_tuple(m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11,
                               m12, m13, m14, m15, m16, m17, m18, m19, m20, m21,
                               m22, m23, m24, m25);
}

template <class T>
auto as_tuple_impl(T &&aggregate,
                             std::integral_constant<size_t, 27>) noexcept {
  auto &[m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11, m12, m13, m14, m15,
         m16, m17, m18, m19, m20, m21, m22, m23, m24, m25, m26] = aggregate;
  return std::forward_as_tuple(m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11,
                               m12, m13, m14, m15, m16, m17, m18, m19, m20, m21,
                               m22, m23, m24, m25, m26);
}

template <class T>
auto as_tuple_impl(T &&aggregate,
                             std::integral_constant<size_t, 28>) noexcept {
  auto &[m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11, m12, m13, m14, m15,
         m16, m17, m18, m19, m20, m21, m22, m23, m24, m25, m26, m27] =
      aggregate;
  return std::forward_as_tuple(m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11,
                               m12, m13, m14, m15, m16, m17, m18, m19, m20, m21,
                               m22, m23, m24, m25, m26, m27);
}

template <class T>
auto as_tuple_impl(T &&aggregate,
                             std::integral_constant<size_t, 29>) noexcept {
  auto &[m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11, m12, m13, m14, m15,
         m16, m17, m18, m19, m20, m21, m22, m23, m24, m25, m26, m27, m28] =
      aggregate;
  return std::forward_as_tuple(m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11,
                               m12, m13, m14, m15, m16, m17, m18, m19, m20, m21,
                               m22, m23, m24, m25, m26, m27, m28);
}

template <class T>
auto as_tuple_impl(T &&aggregate,
                             std::integral_constant<size_t, 30>) noexcept {
  auto &[m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11, m12, m13, m14, m15,
         m16, m17, m18, m19, m20, m21, m22, m23, m24, m25, m26, m27, m28, m29] =
      aggregate;
  return std::forward_as_tuple(m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11,
                               m12, m13, m14, m15, m16, m17, m18, m19, m20, m21,
                               m22, m23, m24, m25, m26, m27, m28, m29);
}

template <class T>
auto as_tuple_impl(T &&aggregate,
                             std::integral_constant<size_t, 31>) noexcept {
  auto &[m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11, m12, m13, m14, m15,
         m16, m17, m18, m19, m20, m21, m22, m23, m24, m25, m26, m27, m28, m29,
         m30] = aggregate;
  return std::forward_as_tuple(m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11,
                               m12, m13, m14, m15, m16, m17, m18, m19, m20, m21,
                               m22, m23, m24, m25, m26, m27, m28, m29, m30);
}

template <class T>
auto as_tuple_impl(T &&aggregate,
                             std::integral_constant<size_t, 32>) noexcept {
  auto &[m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11, m12, m13, m14, m15,
         m16, m17, m18, m19, m20, m21, m22, m23, m24, m25, m26, m27, m28, m29,
         m30, m31] = aggregate;
  return std::forward_as_tuple(m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11,
                               m12, m13, m14, m15, m16, m17, m18, m19, m20, m21,
                               m22, m23, m24, m25, m26, m27, m28, m29, m30,
                               m31);
}

template <class T>
auto as_tuple_impl(T &&aggregate,
                             std::integral_constant<size_t, 33>) noexcept {
  auto &[m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11, m12, m13, m14, m15,
         m16, m17, m18, m19, m20, m21, m22, m23, m24, m25, m26, m27, m28, m29,
         m30, m31, m32] = aggregate;
  return std::forward_as_tuple(m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11,
                               m12, m13, m14, m15, m16, m17, m18, m19, m20, m21,
                               m22, m23, m24, m25, m26, m27, m28, m29, m30, m31,
                               m32);
}

template <class T>
auto as_tuple_impl(T &&aggregate,
                             std::integral_constant<size_t, 34>) noexcept {
  auto &[m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11, m12, m13, m14, m15,
         m16, m17, m18, m19, m20, m21, m22, m23, m24, m25, m26, m27, m28, m29,
         m30, m31, m32, m33] = aggregate;
  return std::forward_as_tuple(m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11,
                               m12, m13, m14, m15, m16, m17, m18, m19, m20, m21,
                               m22, m23, m24, m25, m26, m27, m28, m29, m30, m31,
                               m32, m33);
}

template <class T>
auto as_tuple_impl(T &&aggregate,
                             std::integral_constant<size_t, 35>) noexcept {
  auto &[m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11, m12, m13, m14, m15,
         m16, m17, m18, m19, m20, m21, m22, m23, m24, m25, m26, m27, m28, m29,
         m30, m31, m32, m33, m34] = aggregate;
  return std::forward_as_tuple(m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11,
                               m12, m13, m14, m15, m16, m17, m18, m19, m20, m21,
                               m22, m23, m24, m25, m26, m27, m28, m29, m30, m31,
                               m32, m33, m34);
}

template <class T>
auto as_tuple_impl(T &&aggregate,
                             std::integral_constant<size_t, 36>) noexcept {
  auto &[m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11, m12, m13, m14, m15,
         m16, m17, m18, m19, m20, m21, m22, m23, m24, m25, m26, m27, m28, m29,
         m30, m31, m32, m33, m34, m35] = aggregate;
  return std::forward_as_tuple(m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11,
                               m12, m13, m14, m15, m16, m17, m18, m19, m20, m21,
                               m22, m23, m24, m25, m26, m27, m28, m29, m30, m31,
                               m32, m33, m34, m35);
}

template <class T>
auto as_tuple_impl(T &&aggregate,
                             std::integral_constant<size_t, 37>) noexcept {
  auto &[m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11, m12, m13, m14, m15,
         m16, m17, m18, m19, m20, m21, m22, m23, m24, m25, m26, m27, m28, m29,
         m30, m31, m32, m33, m34, m35, m36] = aggregate;
  return std::forward_as_tuple(m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11,
                               m12, m13, m14, m15, m16, m17, m18, m19, m20, m21,
                               m22, m23, m24, m25, m26, m27, m28, m29, m30, m31,
                               m32, m33, m34, m35, m36);
}

template <class T>
auto as_tuple_impl(T &&aggregate,
                             std::integral_constant<size_t, 38>) noexcept {
  auto &[m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11, m12, m13, m14, m15,
         m16, m17, m18, m19, m20, m21, m22, m23, m24, m25, m26, m27, m28, m29,
         m30, m31, m32, m33, m34, m35, m36, m37] = aggregate;
  return std::forward_as_tuple(m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11,
                               m12, m13, m14, m15, m16, m17, m18, m19, m20, m21,
                               m22, m23, m24, m25, m26, m27, m28, m29, m30, m31,
                               m32, m33, m34, m35, m36, m37);
}

template <class T>
auto as_tuple_impl(T &&aggregate,
                             std::integral_constant<size_t, 39>) noexcept {
  auto &[m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11, m12, m13, m14, m15,
         m16, m17, m18, m19, m20, m21, m22, m23, m24, m25, m26, m27, m28, m29,
         m30, m31, m32, m33, m34, m35, m36, m37, m38] = aggregate;
  return std::forward_as_tuple(m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11,
                               m12, m13, m14, m15, m16, m17, m18, m19, m20, m21,
                               m22, m23, m24, m25, m26, m27, m28, m29, m30, m31,
                               m32, m33, m34, m35, m36, m37, m38);
}

template <class T>
auto as_tuple_impl(T &&aggregate,
                             std::integral_constant<size_t, 40>) noexcept {
  auto &[m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11, m12, m13, m14, m15,
         m16, m17, m18, m19, m20, m21, m22, m23, m24, m25, m26, m27, m28, m29,
         m30, m31, m32, m33, m34, m35, m36, m37, m38, m39] = aggregate;
  return std::forward_as_tuple(m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11,
                               m12, m13, m14, m15, m16, m17, m18, m19, m20, m21,
                               m22, m23, m24, m25, m26, m27, m28, m29, m30, m31,
                               m32, m33, m34, m35, m36, m37, m38, m39);
}

template <class T>
auto as_tuple_impl(T &&aggregate,
                             std::integral_constant<size_t, 41>) noexcept {
  auto &[m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11, m12, m13, m14, m15,
         m16, m17, m18, m19, m20, m21, m22, m23, m24, m25, m26, m27, m28, m29,
         m30, m31, m32, m33, m34, m35, m36, m37, m38, m39, m40] = aggregate;
  return std::forward_as_tuple(m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11,
                               m12, m13, m14, m15, m16, m17, m18, m19, m20, m21,
                               m22, m23, m24, m25, m26, m27, m28, m29, m30, m31,
                               m32, m33, m34, m35, m36, m37, m38, m39, m40);
}

template <class T>
auto as_tuple_impl(T &&aggregate,
                             std::integral_constant<size_t, 42>) noexcept {
  auto &[m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11, m12, m13, m14, m15,
         m16, m17, m18, m19, m20, m21, m22, m23, m24, m25, m26, m27, m28, m29,
         m30, m31, m32, m33, m34, m35, m36, m37, m38, m39, m40, m41] =
      aggregate;
  return std::forward_as_tuple(
      m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11, m12, m13, m14, m15, m16,
      m17, m18, m19, m20, m21, m22, m23, m24, m25, m26, m27, m28, m29, m30, m31,
      m32, m33, m34, m35, m36, m37, m38, m39, m40, m41);
}

template <class T>
auto as_tuple_impl(T &&aggregate,
                             std::integral_constant<size_t, 43>) noexcept {
  auto &[m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11, m12, m13, m14, m15,
         m16, m17, m18, m19, m20, m21, m22, m23, m24, m25, m26, m27, m28, m29,
         m30, m31, m32, m33, m34, m35, m36, m37, m38, m39, m40, m41, m42] =
      aggregate;
  return std::forward_as_tuple(
      m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11, m12, m13, m14, m15, m16,
      m17, m18, m19, m20, m21, m22, m23, m24, m25, m26, m27, m28, m29, m30, m31,
      m32, m33, m34, m35, m36, m37, m38, m39, m40, m41, m42);
}

template <class T>
auto as_tuple_impl(T &&aggregate,
                             std::integral_constant<size_t, 44>) noexcept {
  auto &[m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11, m12, m13, m14, m15,
         m16, m17, m18, m19, m20, m21, m22, m23, m24, m25, m26, m27, m28, m29,
         m30, m31, m32, m33, m34, m35, m36, m37, m38, m39, m40, m41, m42, m43] =
      aggregate;
  return std::forward_as_tuple(
      m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11, m12, m13, m14, m15, m16,
      m17, m18, m19, m20, m21, m22, m23, m24, m25, m26, m27, m28, m29, m30, m31,
      m32, m33, m34, m35, m36, m37, m38, m39, m40, m41, m42, m43);
}

template <class T>
auto as_tuple_impl(T &&aggregate,
                             std::integral_constant<size_t, 45>) noexcept {
  auto &[m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11, m12, m13, m14, m15,
         m16, m17, m18, m19, m20, m21, m22, m23, m24, m25, m26, m27, m28, m29,
         m30, m31, m32, m33, m34, m35, m36, m37, m38, m39, m40, m41, m42, m43,
         m44] = aggregate;
  return std::forward_as_tuple(
      m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11, m12, m13, m14, m15, m16,
      m17, m18, m19, m20, m21, m22, m23, m24, m25, m26, m27, m28, m29, m30, m31,
      m32, m33, m34, m35, m36, m37, m38, m39, m40, m41, m42, m43, m44);
}

template <class T>
auto as_tuple_impl(T &&aggregate,
                             std::integral_constant<size_t, 46>) noexcept {
  auto &[m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11, m12, m13, m14, m15,
         m16, m17, m18, m19, m20, m21, m22, m23, m24, m25, m26, m27, m28, m29,
         m30, m31, m32, m33, m34, m35, m36, m37, m38, m39, m40, m41, m42, m43,
         m44, m45] = aggregate;
  return std::forward_as_tuple(
      m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11, m12, m13, m14, m15, m16,
      m17, m18, m19, m20, m21, m22, m23, m24, m25, m26, m27, m28, m29, m30, m31,
      m32, m33, m34, m35, m36, m37, m38, m39, m40, m41, m42, m43, m44, m45);
}

template <class T>
auto as_tuple_impl(T &&aggregate,
                             std::integral_constant<size_t, 47>) noexcept {
  auto &[m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11, m12, m13, m14, m15,
         m16, m17, m18, m19, m20, m21, m22, m23, m24, m25, m26, m27, m28, m29,
         m30, m31, m32, m33, m34, m35, m36, m37, m38, m39, m40, m41, m42, m43,
         m44, m45, m46] = aggregate;
  return std::forward_as_tuple(m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11,
                               m12, m13, m14, m15, m16, m17, m18, m19, m20, m21,
                               m22, m23, m24, m25, m26, m27, m28, m29, m30, m31,
                               m32, m33, m34, m35, m36, m37, m38, m39, m40, m41,
                               m42, m43, m44, m45, m46);
}

template <class T>
auto as_tuple_impl(T &&aggregate,
                             std::integral_constant<size_t, 48>) noexcept {
  auto &[m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11, m12, m13, m14, m15,
         m16, m17, m18, m19, m20, m21, m22, m23, m24, m25, m26, m27, m28, m29,
         m30, m31, m32, m33, m34, m35, m36, m37, m38, m39, m40, m41, m42, m43,
         m44, m45, m46, m47] = aggregate;
  return std::forward_as_tuple(m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11,
                               m12, m13, m14, m15, m16, m17, m18, m19, m20, m21,
                               m22, m23, m24, m25, m26, m27, m28, m29, m30, m31,
                               m32, m33, m34, m35, m36, m37, m38, m39, m40, m41,
                               m42, m43, m44, m45, m46, m47);
}

template <class T>
auto as_tuple_impl(T &&aggregate,
                             std::integral_constant<size_t, 49>) noexcept {
  auto &[m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11, m12, m13, m14, m15,
         m16, m17, m18, m19, m20, m21, m22, m23, m24, m25, m26, m27, m28, m29,
         m30, m31, m32, m33, m34, m35, m36, m37, m38, m39, m40, m41, m42, m43,
         m44, m45, m46, m47, m48] = aggregate;
  return std::forward_as_tuple(m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11,
                               m12, m13, m14, m15, m16, m17, m18, m19, m20, m21,
                               m22, m23, m24, m25, m26, m27, m28, m29, m30, m31,
                               m32, m33, m34, m35, m36, m37, m38, m39, m40, m41,
                               m42, m43, m44, m45, m46, m47, m48);
}

template <class T>
auto as_tuple_impl(T &&aggregate,
                             std::integral_constant<size_t, 50>) noexcept {
  auto &[m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11, m12, m13, m14, m15,
         m16, m17, m18, m19, m20, m21, m22, m23, m24, m25, m26, m27, m28, m29,
         m30, m31, m32, m33, m34, m35, m36, m37, m38, m39, m40, m41, m42, m43,
         m44, m45, m46, m47, m48, m49] = aggregate;
  return std::forward_as_tuple(m0, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11,
                               m12, m13, m14, m15, m16, m17, m18, m19, m20, m21,
                               m22, m23, m24, m25, m26, m27, m28, m29, m30, m31,
                               m32, m33, m34, m35, m36, m37, m38, m39, m40, m41,
                               m42, m43, m44, m45, m46, m47, m48, m49);
}

template <class T, size_t N>
auto as_tuple_impl(T &&aggregate,
                             std::integral_constant<size_t, N>) noexcept {
  (void)aggregate;
  static_assert(N != N, "aggregate limit reached");
}
} // namespace detail

//--------------------------------------------------------------------------------------------------
// as_tuple
//--------------------------------------------------------------------------------------------------
template <class T, size_t N = tuple_convertible_arity_v<T>>
  requires std::is_aggregate_v<bast::uncvref_t<T>>
auto as_tuple(T&& aggregate) noexcept {
  return detail::as_tuple_impl(aggregate,
                                         std::integral_constant<size_t, N>{});
}
} // namespace bbai::basrf
