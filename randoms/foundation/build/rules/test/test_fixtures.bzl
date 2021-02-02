load(
    "//build/rules:build.bzl",
    _level_3_operation_names = "level_3_operation_names",
    _level_3_visibility = "level_3_visibility",
)
load("//build/rules/cpp:cpp_library.bzl", _cpp_library = "cpp_library")

def test_fixtures(
        name,
        level_1,
        level_2,
        level_3):
    operation_names = _level_3_operation_names(
        level_1 = level_1,
        level_2 = level_2,
        level_3 = level_3,
    )

    for operation_name in operation_names:
        _cpp_library(
            name = operation_name,
            hdrs = ["%s.hpp" % operation_name],
            visibility = _level_3_visibility(
                level_1 = level_1,
                level_2 = level_2,
                level_3 = level_3,
            ),
            deps = [":internal"],
        )
