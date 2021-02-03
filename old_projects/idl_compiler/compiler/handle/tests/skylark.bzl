load("@bazel_skylib//lib:unittest.bzl", "analysistest", "asserts")
load("//old_projects/idl_compiler:build_private.bzl", "IDLHandleInfo")
load("//old_projects/idl_compiler/compiler/handle:build.bzl", "idl_handle")

def _provider_contents_test_impl(ctx):
    env = analysistest.begin(ctx)

    target_under_test = analysistest.target_under_test(env)

    return analysistest.end(env)

_provider_contents_test = analysistest.make(_provider_contents_test_impl)

def _test_provider_contents():
    idl_handle(
        name = "_test_handle",
        src = "//old_projects/idl_compiler/tests/test_data:handle.yaml",
        tags = ["manual"],
    )

    _provider_contents_test(
        name = "handle_provider_contents_test",
        target_under_test = ":_test_handle",
    )

def skylark_test_suite(name):
    _test_provider_contents()

    native.test_suite(
        name = name,
        tests = [
            ":handle_provider_contents_test",
        ],
    )
