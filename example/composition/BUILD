load(
    "//bazel:bbai_component.bzl",
    "bbai_cc_component",
)

bbai_cc_component(
    name = "flight_descriptor1",
    with_test = False,
)

bbai_cc_component(
    name = "trip_descriptor1",
    with_test = False,
    deps = [
        ":flight_descriptor1",
    ],
)

cc_test(
    name = "main1",
    srcs = [
        "main1.cc",
    ],
    deps = [
        ":trip_descriptor1",
    ],
)

bbai_cc_component(
    name = "flight_descriptor2",
    with_test = False,
    deps = [
        "//bbai/base/memory:allocator_aware_helper",
    ],
)

bbai_cc_component(
    name = "trip_descriptor2",
    with_test = False,
    deps = [
        ":flight_descriptor2",
        "//bbai/base/memory:allocator_aware_helper",
    ],
)

cc_test(
    name = "main2",
    srcs = [
        "main2.cc",
    ],
    deps = [
        ":trip_descriptor2",
    ],
)
