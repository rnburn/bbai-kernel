load(
    "//bazel:bbai_component.bzl",
    "bbai_cc_component",
)

bbai_cc_component(
    name = "counting_resource",
)

bbai_cc_component(
    name = "stack",
)

bbai_cc_component(
    name = "stack_extension",
    with_test = False,
    impl_deps = [
        ":stack",
    ],
)

bbai_cc_component(
    name = "stackext_resource",
    impl_deps = [
        ":stack_extension",
    ],
    test_deps = [
        ":counting_resource",
        ":stack_extension",
    ],
)
