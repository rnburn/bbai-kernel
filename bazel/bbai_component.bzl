def bbai_cc_component(
    name, with_test=True, test_deps=[], deps=[], impl_deps = [], **kwargs):
  native.cc_library(
      name = name,
      hdrs = [
          name + ".h",
      ],
      srcs = [
          name + ".cc",
      ],
      deps = deps + impl_deps,
      visibility = ["//visibility:public"],
      **kwargs)
  if with_test:
    native.cc_test(
        name = name + ".t",
        srcs = [
            name + ".t.cc",
        ],
        deps = [
            ":" + name,
            "//bbai/base/test:unit_test",
        ] + deps + test_deps,
        visibility = ["//visibility:public"],
        **kwargs,
    )
