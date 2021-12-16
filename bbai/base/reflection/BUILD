load(
    "//bazel:bbai_component.bzl",
    "bbai_cc_component",
)

bbai_cc_component(
    name = "tuple_convertible_arity",
    deps = [
        "//bbai/base/type:uncvref",
    ],
)

bbai_cc_component(
    name = "tuple_conversion",
    deps = [
        ":tuple_convertible_arity",
        "//bbai/base/type:uncvref",
    ],
)

bbai_cc_component(
    name = "tuple_convertible_get",
    with_test = False,
    deps = [
        ":tuple_conversion",
        ":tuple_convertible_arity",
        "//bbai/base/type:uncvref",
    ],
)

bbai_cc_component(
    name = "element",
    with_test = False,
    deps = [
        ":tuple_conversion",
        ":tuple_convertible_arity",
        "//bbai/base/type:uncvref",
    ],
)

bbai_cc_component(
    name = "member",
    deps = [
        "//bbai/base/type:fixed_string",
    ],
)
