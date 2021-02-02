load("@bazel_skylib//lib:unittest.bzl", "analysistest", "asserts")
load("//idl_compiler:build_private.bzl", "IDLEnumerationInfo")
load("//idl_compiler/compiler/enumeration:build.bzl", "idl_enumeration")

def _provider_contents_test_impl(ctx):
    env = analysistest.begin(ctx)

    target_under_test = analysistest.target_under_test(env)

    return analysistest.end(env)

_provider_contents_test = analysistest.make(_provider_contents_test_impl)

def _test_provider_contents():
    idl_enumeration(
        name = "_test_enumeration",
        src = "//idl_compiler/tests/test_data:enumeration.yaml",
        tags = ["manual"],
    )

    _provider_contents_test(
        name = "enumeration_provider_contents_test",
        target_under_test = ":_test_enumeration",
    )

def skylark_test_suite(name):
    _test_provider_contents()

    native.test_suite(
        name = name,
        tests = [
            ":enumeration_provider_contents_test",
        ],
    )
