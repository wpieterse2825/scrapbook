load("@bazel_skylib//lib:unittest.bzl", "analysistest", "asserts")
load(
    "//old_projects/idl_compiler:build.bzl",
    "idl_handle",
    "idl_enumeration",
    "idl_structure",
    "idl_function",
    "idl_archive",
    "IDLArchiveInfo",
)

def _provider_contents_test_impl(ctx):
    env = analysistest.begin(ctx)

    target_under_test = analysistest.target_under_test(env)

    return analysistest.end(env)

_provider_contents_test = analysistest.make(_provider_contents_test_impl)

def _test_provider_contents():
    idl_handle(
        name = "_test_archive_handle",
        src = "//old_projects/idl_compiler/tests/test_data:handle.yaml",
    )

    idl_enumeration(
        name = "_test_archive_enumeration",
        src = "//old_projects/idl_compiler/tests/test_data:enumeration.yaml",
    )

    idl_structure(
        name = "_test_archive_structure",
        src = "//old_projects/idl_compiler/tests/test_data:structure.yaml",
    )

    idl_function(
        name = "_test_archive_function",
        src = "//old_projects/idl_compiler/tests/test_data:function.yaml",
    )

    idl_archive(
        name = "_test_archive_archive",
        deps = [
            ":_test_archive_handle",
            ":_test_archive_enumeration",
            ":_test_archive_structure",
            ":_test_archive_function",
        ],
    )

    _provider_contents_test(
        name = "archive_provider_contents_test",
        target_under_test = ":_test_archive_archive",
    )

def skylark_test_suite(name):
    _test_provider_contents()

    native.test_suite(
        name = name,
        tests = [
            ":archive_provider_contents_test",
        ],
    )
