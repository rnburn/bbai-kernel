load(
    "//bazel:stackext_build_system.bzl",
    "stackext_cc_library",
    "stackext_package",
)

stackext_package()

# From commit a575536abe20b58c48863600f8a71e93b4052b81
stackext_cc_library(
    name = "catch2",
    hdrs = [
        "catch.hpp",
    ],
    is_3rd_party = True,
)

stackext_cc_library(
    name = "main_lib",
    srcs = [
        "catch_main.cpp",
    ],
    deps = [
        ":catch2",
    ],
    is_3rd_party = True,
)
