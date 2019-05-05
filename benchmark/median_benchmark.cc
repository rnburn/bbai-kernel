#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

#include "stackext/scoped_allocator.h"

struct employee {
  double salary;
};

static thread_local auto StackExtension =
    stackext::linear_allocator{1024 * 1024};

static double compute_median_salary1(const std::vector<employee>& workforce) {
  assert(!workforce.empty());
  std::vector<double> salaries;
  salaries.reserve(workforce.size());
  for (auto& employee : workforce) {
    salaries.push_back(employee.salary);
  }
  auto midpoint = salaries.begin() + salaries.size() / 2;
  std::nth_element(salaries.begin(), midpoint, salaries.end());
  if (salaries.size() % 2 == 1) {
    return *midpoint;
  }
  return (*std::max_element(salaries.begin(), midpoint) + *midpoint) / 2.0;
}

static double compute_median_salary2(const std::vector<employee>& workforce) {
  assert(!workforce.empty());
  stackext::scoped_allocator allocator{StackExtension};
  auto salaries = allocator.allocate<double>(workforce.size());
  std::transform(workforce.begin(), workforce.end(), salaries,
                 [](const employee& employee) { return employee.salary; });
  auto midpoint = salaries + workforce.size() / 2;
  std::nth_element(salaries, midpoint, salaries + workforce.size());
  if (workforce.size() % 2 == 1) {
    return *midpoint;
  }
  return (*std::max_element(salaries, midpoint) + *midpoint) / 2.0;
}

int main() {
  std::cout << compute_median_salary1({{50.0}}) << "\n";
  std::cout << compute_median_salary1({{100.0}, {50.0}}) << "\n";
  std::cout << compute_median_salary1({{100.0}, {25.0}, {50.0}}) << "\n";
  std::cout << compute_median_salary1({{100.0}, {25.0}, {200.0}, {50.0}})
            << "\n";

  std::cout << "--------------\n";

  std::cout << compute_median_salary2({{50.0}}) << "\n";
  std::cout << compute_median_salary2({{100.0}, {50.0}}) << "\n";
  std::cout << compute_median_salary2({{100.0}, {25.0}, {50.0}}) << "\n";
  std::cout << compute_median_salary2({{100.0}, {25.0}, {200.0}, {50.0}})
            << "\n";
  return 0;
}
