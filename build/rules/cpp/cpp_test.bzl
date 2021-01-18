load("@rules_cc//cc:defs.bzl", _bazel_cpp_test = "cc_test")

def cpp_test(name, **kwargs):
    _bazel_cpp_test(
        name = name,
        **kwargs
    )
