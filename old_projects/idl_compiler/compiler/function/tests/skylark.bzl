load("@bazel_skylib//lib:unittest.bzl", "analysistest", "asserts")
load("//old_projects/idl_compiler:build_private.bzl", "IDLFunctionInfo")
load("//old_projects/idl_compiler/compiler/function:build.bzl", "idl_function")

def _provider_contents_test_impl(ctx):
    env = analysistest.begin(ctx)

    target_under_test = analysistest.target_under_test(env)

    return analysistest.end(env)

_provider_contents_test = analysistest.make(_provider_contents_test_impl)

def _test_provider_contents():
    idl_function(
        name = "_test_function",
        src = "//old_projects/idl_compiler/tests/test_data:function.yaml",
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
