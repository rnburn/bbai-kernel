#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>
#include <random>

#include "stackext/scoped_allocator.h"

#include "benchmark/benchmark.h"

struct employee {
  double salary;
};

static thread_local auto StackExtension =
    stackext::linear_allocator{1024 * 1024};

static std::vector<std::vector<employee>> make_random_workforces() {
  std::mt19937 random_number_generator{0};
  std::vector<std::vector<employee>> result;
  const int num_workforces = 1000;
  result.reserve(num_workforces);
  std::uniform_int_distribution<int> num_employees_distribution{1, 10};
  std::uniform_real_distribution<double> salary_distribution{0, 1000000};
  for (int i=0; i<num_workforces; ++i) {
    auto num_employees = num_employees_distribution(random_number_generator);
    std::vector<employee> workforce;
    workforce.reserve(num_employees);
    for (int j=0; j<num_employees; ++j) {
      workforce.push_back(employee{salary_distribution(random_number_generator)});
    }
    result.emplace_back(std::move(workforce));
  }
  return result;
}

static double compute_median_salary_heap(const std::vector<employee>& workforce) {
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

static double compute_median_salary_stackext(const std::vector<employee>& workforce) {
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

static void BM_compute_median_salary_heap(benchmark::State& state) {
  auto workforces = make_random_workforces();
  for (auto _ : state) {
    for (auto& workforce : workforces) {
      auto median_salary = compute_median_salary_heap(workforce);
      benchmark::DoNotOptimize(median_salary);
    }
  }
}

BENCHMARK(BM_compute_median_salary_heap);

static void BM_compute_median_salary_stackext(benchmark::State& state) {
  auto workforces = make_random_workforces();
  for (auto _ : state) {
    for (auto& workforce : workforces) {
      auto median_salary = compute_median_salary_stackext(workforce);
      benchmark::DoNotOptimize(median_salary);
    }
  }
}

BENCHMARK(BM_compute_median_salary_stackext);

BENCHMARK_MAIN();
