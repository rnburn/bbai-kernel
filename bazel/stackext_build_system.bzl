def stackext_package():
    native.package(default_visibility = ["//visibility:public"])

# Taken from https://github.com/bazelbuild/bazel/issues/2670#issuecomment-369674735
# with modifications.
def stackext_private_include_copts(includes, is_system=False):
    copts = []
    prefix = ''

    # convert "@" to "external/" unless in the main workspace
    repo_name = native.repository_name()
    if repo_name != '@':
        prefix = 'external/{}/'.format(repo_name[1:])

    inc_flag = "-isystem " if is_system else "-I"

    for inc in includes:
        copts.append("{}{}{}".format(inc_flag, prefix, inc))
        copts.append("{}$(GENDIR){}/{}".format(inc_flag, prefix, inc))

    return copts

def stackext_include_copts():
  return stackext_private_include_copts([
      "include",
      "src",
      "test",
  ]) + stackext_private_include_copts([
    "3rd_party/randutils/include", 
    "3rd_party/base64/include", 
  ], is_system=True)

def stackext_copts(is_3rd_party=False):
  if is_3rd_party:
    return [
      "-std=c++11",
    ]
  return [
      "-Wall",
      "-Wextra",
      "-Werror",
      "-Wnon-virtual-dtor",
      "-Woverloaded-virtual",
      "-Wold-style-cast",
      "-Wno-overloaded-virtual",
      "-Wno-missing-field-initializers",
      "-Wvla",
      "-std=c++11",
  ]


def stackext_include_prefix(path):
    if path.startswith('src/') or path.startswith('include/'):
        return '/'.join(path.split('/')[1:])
    return None

def stackext_cc_library(name,
                     srcs = [],
                     hdrs = [],
                     private_hdrs = [],
                     copts = [],
                     linkopts = [],
                     includes = [],
                     visibility = None,
                     external_deps = [],
                     deps = [],
                     data = [],
                     is_3rd_party = False,
                     strip_include_prefix = None):
  native.cc_library(
      name = name,
      srcs = srcs + private_hdrs,
      hdrs = hdrs,
      copts = stackext_include_copts() + stackext_copts(is_3rd_party) + copts,
      linkopts = linkopts,
      includes = includes,
      deps = external_deps + deps,
      data = data,
      linkstatic = 1,
      include_prefix = stackext_include_prefix(native.package_name()),
      visibility = visibility,
      strip_include_prefix = strip_include_prefix,
  )

def stackext_cc_binary(
        name,
        args = [],
        srcs = [],
        data = [],
        copts = [],
        linkshared = False,
        testonly = 0,
        visibility = None,
        external_deps = [],
        deps = [],
        linkopts = []):
    native.cc_binary(
        name = name,
        args = args,
        srcs = srcs,
        data = data,
        copts = stackext_include_copts() + stackext_copts() + copts,
        linkopts = linkopts,
        linkshared = linkshared,
        testonly = testonly,
        linkstatic = 1,
        visibility = visibility,
        stamp = 1,
        deps = external_deps + deps,
    )

def stackext_cc_test(
        name,
        args = [],
        copts = [],
        srcs = [],
        data = [],
        testonly = 0,
        visibility = None,
        external_deps = [],
        deps = [],
        linkopts = []):
    native.cc_test(
        name = name,
        args = args,
        srcs = srcs,
        data = data,
        copts = stackext_include_copts() + stackext_copts() + copts,
        linkopts = linkopts,
        testonly = testonly,
        linkstatic = 1,
        visibility = visibility,
        stamp = 1,
        deps = external_deps + deps,
    )

def stackext_catch_test(
        name,
        srcs = [],
        data = [],
        visibility = None,
        external_deps = [],
        deps = [],
        linkopts = []):
    stackext_cc_test(
        name = name,
        srcs = srcs,
        data = data,
        linkopts = linkopts,
        visibility = visibility,
        deps = deps,
        external_deps = external_deps + ["//3rd_party/catch2:main_lib"],
    )
