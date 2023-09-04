#include "benchmark/benchmark.h"

#include <string_view>

#include "bbai/memory/resource/stackext_resource.h"

#include "parse_json1.h"
#include "parse_json2.h"
#include "sum1.h"
#include "sum2.h"
using namespace bbai;
using namespace bbai::jsonex;

const std::string_view s1 = R"(
[
  1, 7, -2,
  [10, -12, 100, 15, -77],
  [[10], [9, 2], [[37]]],
  [[[[]]], [8, -9, [-8, [-1, [10, [5], 8]]]]],
  [1, [2, [3, [4, [5, [6, [7, [8, [9, [10, 11, 12]]]]]]]]]]
]
)";

static void BM_parse_sum_json_managed_stackext(benchmark::State& state) {
  // Perform setup here
  for (auto _ : state) {
    memr::stackext_resource resource;
    memmg::managed_ptr<json_value> json{&resource};
    parse_json(json, s1);
    auto sum = sum1(json.get());
    benchmark::DoNotOptimize(sum);
  }
}
BENCHMARK(BM_parse_sum_json_managed_stackext);

static void BM_parse_sum_json_managed_stackext_wink(benchmark::State& state) {
  // Perform setup here
  for (auto _ : state) {
    memr::stackext_resource resource;
    std::pmr::polymorphic_allocator<> alloc{&resource};
    auto json = alloc.new_object<memmg::managed_ptr<json_value>>();
    parse_json(*json, s1);
    auto sum = sum1(json->get());
    benchmark::DoNotOptimize(sum);
  }
}
BENCHMARK(BM_parse_sum_json_managed_stackext_wink);

static void BM_parse_sum_json_unique(benchmark::State& state) {
  // Perform setup here
  for (auto _ : state) {
    std::unique_ptr<json_value> json;
    parse_json(json, s1);
    auto sum = sum2(json.get());
    benchmark::DoNotOptimize(sum);
  }
}
BENCHMARK(BM_parse_sum_json_unique);

// Run the benchmark
BENCHMARK_MAIN();
