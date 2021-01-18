load("@bazel_skylib//lib:unittest.bzl", "analysistest", "asserts")
load("//tools/idl:build_private.bzl", "IDLFunctionInfo")
load("//tools/idl/compiler/function:build.bzl", "idl_function")

def _provider_contents_test_impl(ctx):
    env = analysistest.begin(ctx)

    target_under_test = analysistest.target_under_test(env)

    return analysistest.end(env)

_provider_contents_test = analysistest.make(_provider_contents_test_impl)

def _test_provider_contents():
    idl_function(
        name = "_test_function",
        src = "//tools/idl/tests/test_data:function.yaml",
        tags = ["manual"],
    )

    _provider_contents_test(
        name = "function_provider_contents_test",
        target_under_test = ":_test_function",
    )

def skylark_test_suite(name):
    _test_provider_contents()

    native.test_suite(
        name = name,
        tests = [
            ":function_provider_contents_test",
        ],
    )
