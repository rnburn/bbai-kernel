#include "benchmark/benchmark.h"

// Benchmarks stackext for a function that computes the median salary of a
// std::vector of employees.

#include <cassert>
#include <iostream>
#include <random>
#include <vector>

#include "employee.h"
#include "median_salary1.h"
#include "median_salary2.h"
using namespace bbai;
using namespace bbai::medex;

static std::vector<std::vector<employee>> make_random_workforces() {
  std::mt19937 random_number_generator{0};
  std::vector<std::vector<employee>> result;
  const int num_workforces = 1000;
  result.reserve(num_workforces);
  std::uniform_int_distribution<int> num_employees_distribution{1, 20};
  std::uniform_real_distribution<double> salary_distribution{0, 1000000};
  for (int i = 0; i < num_workforces; ++i) {
    auto num_employees = num_employees_distribution(random_number_generator);
    std::vector<employee> workforce;
    workforce.reserve(num_employees);
    for (int j = 0; j < num_employees; ++j) {
      workforce.push_back(
          employee{salary_distribution(random_number_generator)});
    }
    result.emplace_back(std::move(workforce));
  }
  return result;
}

static void BM_compute_median_salary_heap(benchmark::State& state) {
  auto workforces = make_random_workforces();
  for (auto _ : state) {
    for (auto& workforce : workforces) {
      auto median_salary = compute_median_salary2(
          workforce.data(), workforce.data() + workforce.size());
      benchmark::DoNotOptimize(median_salary);
    }
  }
}

BENCHMARK(BM_compute_median_salary_heap);

static void BM_compute_median_salary_stackext(benchmark::State& state) {
  auto workforces = make_random_workforces();
  for (auto _ : state) {
    for (auto& workforce : workforces) {
      auto median_salary = compute_median_salary1(
          workforce.data(), workforce.data() + workforce.size());
      benchmark::DoNotOptimize(median_salary);
    }
  }
}

BENCHMARK(BM_compute_median_salary_stackext);

BENCHMARK_MAIN();
