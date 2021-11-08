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
