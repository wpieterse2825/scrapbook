load("@rules_cc//cc:defs.bzl", _bazel_cpp_library = "cc_library")

def cpp_library(name, **kwargs):
    _bazel_cpp_library(
        name = name,
        **kwargs
    )
