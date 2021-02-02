load("@rules_cc//cc:defs.bzl", _bazel_cpp_binary = "cc_binary")

def cpp_binary(name, **kwargs):
    _bazel_cpp_binary(
        name = name,
        **kwargs
    )
