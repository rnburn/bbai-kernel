// Benchmarks stackext for a function that uses std::map to aggregate film sales
// and return the film with the highest gross.

#include <algorithm>
#include <cassert>
#include <iostream>
#include <random>
#include <vector>
#include <map>
#include <string>

#include "stackext/scoped_allocator.h"
#include "stackext/linear_allocator.h"

#include "benchmark/benchmark.h"

static thread_local auto StackExtension =
    stackext::stack_allocator{1024 * 1024};

static std::vector<std::vector<std::pair<std::string, double>>>
make_random_film_sales_set() {
  std::mt19937 random_number_generator{0};
  std::vector<std::vector<std::pair<std::string, double>>> result;
  const int num_film_sales = 1000;
  result.reserve(num_film_sales);
  std::vector<std::string> films = {"Avatar",      "Indiana Jones", "Ishtar",
                                    "Godfather",   "Pulp Fiction",  "Aliens",
                                    "Blade Runner"};
  std::uniform_int_distribution<int> num_films_distribution{1, 10};
  std::uniform_int_distribution<int> film_distribution{
      0, static_cast<int>(films.size()) - 1};
  std::uniform_real_distribution<double> sales_distribution{0, 1000};
  for (int i = 0; i < num_film_sales; ++i) {
    int num_films = num_films_distribution(random_number_generator);
    std::vector<std::pair<std::string, double>> film_sales;
    film_sales.reserve(num_films);
    for (int j = 0; j < num_films; ++j) {
      film_sales.emplace_back(films[film_distribution(random_number_generator)],
                              sales_distribution(random_number_generator));
    }
    result.emplace_back(std::move(film_sales));
  }
  return result;
}

static std::pair<std::string_view, double> compute_top_film_heap(
    const std::vector<std::pair<std::string, double>>& film_sales) {
  assert(!film_sales.empty());
  std::map<std::string_view, double> film_totals;
  for (auto& film : film_sales) {
    film_totals[film.first] += film.second;
  }
  return *std::max_element(film_totals.begin(), film_totals.end(),
                           [](const std::pair<std::string_view, double>& lhs,
                              const std::pair<std::string_view, double>& rhs) {
                             return lhs.second < rhs.second;
                           });
}

static std::pair<std::string_view, double> compute_top_film_stackext(
    const std::vector<std::pair<std::string, double>>& film_sales) {
  assert(!film_sales.empty());
  stackext::scoped_allocator allocator{StackExtension};
  using value_type = std::pair<const std::string_view, double>;
  using map_type =
      std::map<std::string_view, double, std::less<std::string_view>,
               stackext::linear_allocator<value_type>>;
  map_type film_totals{stackext::linear_allocator<value_type>{allocator}};
  for (auto& film : film_sales) {
    film_totals[film.first] += film.second;
  }
  return *std::max_element(film_totals.begin(), film_totals.end(),
                           [](const value_type& lhs, const value_type& rhs) {
                             return lhs.second < rhs.second;
                           });
}

static void BM_compute_top_film_heap(benchmark::State& state) {
  auto film_sales_set = make_random_film_sales_set();
  for (auto _ : state) {
    for (auto& film_sales : film_sales_set) {
      auto top_film = compute_top_film_heap(film_sales);
      benchmark::DoNotOptimize(top_film);
    }
  }
}

BENCHMARK(BM_compute_top_film_heap);

static void BM_compute_top_film_stackext(benchmark::State& state) {
  auto film_sales_set = make_random_film_sales_set();
  for (auto _ : state) {
    for (auto& film_sales : film_sales_set) {
      auto top_film = compute_top_film_stackext(film_sales);
      benchmark::DoNotOptimize(top_film);
    }
  }
}

BENCHMARK(BM_compute_top_film_stackext);

BENCHMARK_MAIN();
