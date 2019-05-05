load(
    "//bazel:stackext_build_system.bzl",
    "stackext_catch_test",
)

stackext_catch_test(
    name = "stack_allocator_test",
    srcs = [
        "stack_allocator_test.cc",
    ],
    deps = [
        "//:stackext_lib",
    ],
)

stackext_catch_test(
    name = "scoped_allocator_test",
    srcs = [
        "scoped_allocator_test.cc",
    ],
    deps = [
        "//:stackext_lib",
    ],
)

stackext_catch_test(
    name = "utility_test",
    srcs = [
        "utility_test.cc",
    ],
    deps = [
        "//:stackext_lib",
    ],
)
