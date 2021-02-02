load("@bazel_skylib//lib:unittest.bzl", "analysistest", "asserts")
load("//tools/idl:build_private.bzl", "IDLStructureInfo")
load("//tools/idl/compiler/structure:build.bzl", "idl_structure")

def _provider_contents_test_impl(ctx):
    env = analysistest.begin(ctx)

    target_under_test = analysistest.target_under_test(env)

    return analysistest.end(env)

_provider_contents_test = analysistest.make(_provider_contents_test_impl)

def _test_provider_contents():
    idl_structure(
        name = "_test_structure",
        src = "//tools/idl/tests/test_data:structure.yaml",
        tags = ["manual"],
    )

    _provider_contents_test(
        name = "structure_provider_contents_test",
        target_under_test = ":_test_structure",
    )

def skylark_test_suite(name):
    _test_provider_contents()

    native.test_suite(
        name = name,
        tests = [
            ":structure_provider_contents_test",
        ],
    )
