load(
    "//bazel:stackext_build_system.bzl",
    "stackext_package",
    "stackext_cc_test",
)

stackext_package()

stackext_cc_test(
    name = "tutorial",
    srcs = [
        "tutorial.cc",
    ],
    deps = [
        "//:stackext_lib",
    ],
)
