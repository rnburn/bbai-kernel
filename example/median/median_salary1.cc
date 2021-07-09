#include "median_salary1.h"

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <iterator>

#include "bbai/memory/resource/stackext_resource.h"

#include "employee.h"

namespace bbai::medex {
//--------------------------------------------------------------------------------------------------
// compute_median_salary1
//--------------------------------------------------------------------------------------------------
double compute_median_salary1(const employee* first, const employee* last) noexcept {
  assert(first != last);
  memr::stackext_resource resource;
  std::pmr::polymorphic_allocator<double> alloc{&resource};

  auto n = static_cast<size_t>(std::distance(first, last));
  auto salaries = alloc.allocate(n);
  for (size_t i=0; i<n; ++i) {
    salaries[i] = first[i].salary;
  }
  auto midpoint = salaries + n / 2;
  std::nth_element(salaries, midpoint, salaries + n);
  if (n % 2 == 1) {
    return *midpoint;
  }
  return (*std::max_element(salaries, midpoint) + *midpoint) / 2.0;
}
} // namespace bbai::medex
