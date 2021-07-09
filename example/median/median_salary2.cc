#include "median_salary2.h"

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <iterator>
#include <vector>

#include "employee.h"

namespace bbai::medex {
//--------------------------------------------------------------------------------------------------
// compute_median_salary2
//--------------------------------------------------------------------------------------------------
double compute_median_salary2(const employee* first, const employee* last) noexcept {
  assert(first != last);

  auto n = static_cast<size_t>(std::distance(first, last));
  std::vector<double> salaries;
  salaries.reserve(n);
  for (; first != last; ++first) {
    salaries.push_back(first->salary);
  }
  auto midpoint = salaries.begin() + salaries.size() / 2;
  std::nth_element(salaries.begin(), midpoint, salaries.end());
  if (salaries.size() % 2 == 1) {
    return *midpoint;
  }
  return (*std::max_element(salaries.begin(), midpoint) + *midpoint) / 2.0;
}
} // namespace bbai::medex
