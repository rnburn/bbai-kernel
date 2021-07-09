load(
    "//bazel:bbai_component.bzl",
    "bbai_cc_component",
)

bbai_cc_component(
    name = "managed_ptr",
    deps = [
        ":pointer_operator",
    ],
)

bbai_cc_component(
    name = "managed_ptr_utility",
    with_test = False,
    deps = [
        ":managed_ptr",
    ],
)

bbai_cc_component(
    name = "pointer_operator",
    deps = [
        ":pointer_operator_function",
    ],
)

bbai_cc_component(
    name = "pointer_operator_function",
)
