load("@bazel_skylib//lib:unittest.bzl", "analysistest", "asserts")
load(
    "//idl_compiler:build.bzl",
    "idl_handle",
    "idl_enumeration",
    "idl_structure",
    "idl_function",
    "idl_archive",
    "idl_generator_c",
    "IDLGeneratorInfo",
)

def _provider_contents_test_impl(ctx):
    env = analysistest.begin(ctx)

    target_under_test = analysistest.target_under_test(env)

    return analysistest.end(env)

_provider_contents_test = analysistest.make(_provider_contents_test_impl)

def _test_provider_contents():
    idl_handle(
        name = "_test_c_generator_handle",
        src = "//idl_compiler/tests/test_data:handle.yaml",
    )

    idl_enumeration(
        name = "_test_c_generator_enumeration",
        src = "//idl_compiler/tests/test_data:enumeration.yaml",
    )

    idl_structure(
        name = "_test_c_generator_structure",
        src = "//idl_compiler/tests/test_data:structure.yaml",
    )

    idl_function(
        name = "_test_c_generator_function",
        src = "//idl_compiler/tests/test_data:function.yaml",
    )

    idl_archive(
        name = "_test_c_generator_archive",
        deps = [
            ":_test_c_generator_handle",
            ":_test_c_generator_enumeration",
            ":_test_c_generator_structure",
            ":_test_c_generator_function",
        ],
    )

    idl_generator_c(
        name = "_test_c_generator",
        dep = ":_test_c_generator_archive",
        tags = ["manual"],
    )

    _provider_contents_test(
        name = "c_generator_provider_contents_test",
        target_under_test = ":_test_c_generator",
    )

def skylark_test_suite(name):
    _test_provider_contents()

    native.test_suite(
        name = name,
        tests = [
            ":c_generator_provider_contents_test",
        ],
    )
