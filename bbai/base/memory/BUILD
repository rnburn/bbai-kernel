load(
    "//bazel:bbai_component.bzl",
    "bbai_cc_component",
)

bbai_cc_component(
    name = "allocator_aware_helper",
    deps = [
        "//bbai/base/concept:allocator_aware",
        "//bbai/base/reflection:tuple_convertible_arity",
        "//bbai/base/reflection:tuple_convertible_get",
        "//bbai/base/reflection:tuple_conversion",
        "//bbai/base/reflection:element",
        "//bbai/base/type:uncvref",
    ],
)
