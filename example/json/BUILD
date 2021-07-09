load(
    "//bazel:bbai_component.bzl",
    "bbai_cc_component",
)

bbai_cc_component(
    name = "json_value_type",
    with_test = False,
)

bbai_cc_component(
    name = "json_value",
    with_test = False,
    deps = [
        ":json_value_type",
    ],
)

bbai_cc_component(
    name = "json_parse_error",
    with_test = False,
)

bbai_cc_component(
    name = "json_array1",
    with_test = False,
    deps = [
        ":json_value",
        "//bbai/memory/management:managed_ptr",
    ],
)

bbai_cc_component(
    name = "json_array2",
    with_test = False,
    deps = [
        ":json_value",
    ],
)

bbai_cc_component(
    name = "json_number",
    with_test = False,
    deps = [
        ":json_value",
    ],
)

bbai_cc_component(
    name = "parse_json1",
    deps = [
        ":json_value",
        ":json_array1",
        ":json_parse_error",
        ":json_number",
        ":parse_number",
        ":whitespace",
        "//bbai/memory/management:managed_ptr",
        "//bbai/memory/management:managed_ptr_utility",
        "//bbai/memory/resource:stackext_resource",
    ],
)

bbai_cc_component(
    name = "parse_json2",
    deps = [
        ":json_value",
        ":json_array2",
        ":json_parse_error",
        ":json_number",
        ":parse_number",
        ":whitespace",
    ],
)

bbai_cc_component(
    name = "parse_number",
    deps = [
        ":json_parse_error",
    ],
)

bbai_cc_component(
    name = "sum1",
    impl_deps = [
        ":json_value",
        ":json_array1",
        ":json_number",
    ],
    test_deps = [
        ":parse_json1",
    ],
)

bbai_cc_component(
    name = "sum2",
    impl_deps = [
        ":json_value",
        ":json_array2",
        ":json_number",
    ],
    test_deps = [
        ":parse_json2",
    ],
)

bbai_cc_component(
    name = "whitespace",
    with_test = False,
)

cc_binary(
    name = "benchmark",
    srcs = [
        "benchmark.cc",
    ],
    deps = [
        ":parse_json1",
        ":parse_json2",
        ":sum1",
        ":sum2",
        "//bbai/memory/resource:stackext_resource",
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
        ":parse_json1",
        ":parse_json2",
        ":sum1",
        ":sum2",
        "//bbai/memory/resource:stackext_resource",
        "@com_google_benchmark//:benchmark",
    ],
)
