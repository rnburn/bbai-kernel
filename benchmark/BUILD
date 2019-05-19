load(
    "//bazel:stackext_build_system.bzl",
    "stackext_package",
    "stackext_cc_binary",
    "stackext_cc_test",
)

stackext_package()

stackext_cc_binary(
    name = "median_salary_benchmark",
    srcs = [
      "median_salary_benchmark.cc",
    ],
    deps = [
        "//:stackext_lib",
    ],
    external_deps = [
      "@com_google_benchmark//:benchmark",
    ],
)

stackext_cc_test(
    name = "median_salary_benchmark_test",
    srcs = [
      "median_salary_benchmark.cc",
    ],
    args = ["--benchmark_min_time=0"],
    deps = [
        "//:stackext_lib",
    ],
    external_deps = [
      "@com_google_benchmark//:benchmark",
    ],
)

stackext_cc_binary(
    name = "top_film_benchmark",
    srcs = [
        "top_film_benchmark.cc",
    ],
    deps = [
        "//:stackext_lib",
    ],
    copts = [
        "-std=c++17",
    ],
    external_deps = [
      "@com_google_benchmark//:benchmark",
    ],
)

stackext_cc_test(
    name = "top_film_benchmark_test",
    srcs = [
      "top_film_benchmark.cc",
    ],
    args = ["--benchmark_min_time=0"],
    deps = [
        "//:stackext_lib",
    ],
    copts = [
        "-std=c++17",
    ],
    external_deps = [
      "@com_google_benchmark//:benchmark",
    ],
)
