load(
    "//bazel:stackext_build_system.bzl",
    "stackext_package",
    "stackext_cc_binary",
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
