load(
    "//bazel:stackext_build_system.bzl",
    "stackext_package",
    "stackext_cc_binary",
    "stackext_cc_test",
)

stackext_package()

stackext_cc_binary(
    name = "median_benchmark",
    srcs = [
      "median_benchmark.cc",
    ],
    deps = [
        "//:stackext_lib",
    ],
    external_deps = [
      "@com_google_benchmark//:benchmark",
    ],
)

stackext_cc_test(
    name = "median_benchmark_test",
    srcs = [
      "median_benchmark.cc",
    ],
    args = ["--benchmark_min_time=0"],
    deps = [
        "//:stackext_lib",
    ],
    external_deps = [
      "@com_google_benchmark//:benchmark",
    ],
)
