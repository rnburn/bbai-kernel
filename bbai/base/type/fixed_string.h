#pragma once

#include <array>
#include <cstddef>
#include <string_view>

namespace bbai::bast {
//--------------------------------------------------------------------------------------------------
// fixed_string
//--------------------------------------------------------------------------------------------------
template <size_t N>
class fixed_string {
 public:
   constexpr fixed_string() noexcept = default;

   constexpr fixed_string(const char (&array)[N+1]) noexcept {
     std::copy(array, array + N + 1, data_.data());
   }

   constexpr auto operator<=>(const fixed_string&) const noexcept = default;

   constexpr size_t size() const noexcept { return N; }
   constexpr bool empty() const noexcept { return N == 0; }

   constexpr char &operator[](size_t index) noexcept { return data_[index]; }
   constexpr const char &operator[](size_t index) const noexcept {
     return data_[index];
   }

   constexpr char* data() noexcept { return data_.data(); }
   constexpr const char* data() const noexcept { return data_.data(); }

   constexpr char *begin() { return data_.data(); }
   constexpr char *end() { return data_.data() + N; }

   constexpr const char* begin() const { return data_.data(); }
   constexpr const char *end() const { return data_.data() + N; }

   constexpr operator std::string_view() const noexcept {
     return {this->data(), N};
   }

 private:  
   std::array<char, N + 1> data_;
};

template <size_t N>
fixed_string(const char (&)[N]) -> fixed_string<N-1>;
} // namespace bbai::bast
