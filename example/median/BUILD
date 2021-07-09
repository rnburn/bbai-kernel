load(
    "//bazel:bbai_component.bzl",
    "bbai_cc_component",
)

bbai_cc_component(
    name = "employee",
    with_test = False,
)

bbai_cc_component(
    name = "median_salary1",
    impl_deps = [
        ":employee",
        "//bbai/memory/resource:stackext_resource",
    ],
    test_deps = [
        ":employee",
    ],
)

bbai_cc_component(
    name = "median_salary2",
    impl_deps = [
        ":employee",
    ],
    test_deps = [
        ":employee",
    ],
)

cc_binary(
    name = "benchmark",
    srcs = [
        "benchmark.cc",
    ],
    deps = [
        ":employee",
        ":median_salary1",
        ":median_salary2",
        "@com_google_benchmark//:benchmark",
    ],
)

cc_test(
    name = "benchmark_test",
    srcs = [
        "benchmark.cc",
    ],
    args = ["--benchmark_min_time=0"],
    deps = [
        ":employee",
        ":median_salary1",
        ":median_salary2",
        "@com_google_benchmark//:benchmark",
    ],
)
