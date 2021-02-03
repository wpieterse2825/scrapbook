load("@bazel_skylib//lib:unittest.bzl", "analysistest", "asserts")
load("//old_projects/idl_compiler:build_private.bzl", "IDLGeneratorPropertiesInfo")
load("//old_projects/idl_compiler/generator/generator_props:build.bzl", "idl_generator_props")

def _provider_contents_test_impl(ctx):
    env = analysistest.begin(ctx)

    target_under_test = analysistest.target_under_test(env)

    return analysistest.end(env)

_provider_contents_test = analysistest.make(_provider_contents_test_impl)

def _test_provider_contents():
    idl_generator_props(
        name = "_test_generator_props",
        tags = ["manual"],
    )

    _provider_contents_test(
        name = "generator_props_provider_contents_test",
        target_under_test = ":_test_generator_props",
    )

def skylark_test_suite(name):
    _test_provider_contents()

    native.test_suite(
        name = name,
        tests = [
            ":generator_props_provider_contents_test",
        ],
    )
