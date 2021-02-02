load("//randoms/foundation/build/rules:build.bzl", _level_3_operations = "level_3_operations")
load("//randoms/foundation/build/rules/cpp:cpp_test.bzl", _cpp_test = "cpp_test")
load(
    "//randoms/foundation/build/rules/test:test_source.bzl",
    _test_source = "test_source",
    _test_source_name = "test_source_name",
)

def test(
        name,
        level_1,
        level_2,
        level_3,
        level_3_platform,
        level_3_implementation,
        level_3_operation):
    target_generated = "_test_generated_%s" % level_3_operation
    target_copy = "_test_copy_%s" % level_3_operation
    target_test = "test_%s" % level_3_operation
    source_name = "%s.cpp" % _test_source_name(level_3_operation = level_3_operation)

    _test_source(
        name = target_generated,
        level_1 = level_1,
        level_2 = level_2,
        level_3 = level_3,
        level_3_platform = level_3_platform,
        level_3_implementation = level_3_implementation,
        level_3_operation = level_3_operation,
    )

    native.genrule(
        name = target_copy,
        srcs = [":%s" % target_generated],
        outs = [source_name],
        cmd = "cp $(SRCS) $@",
    )

    _cpp_test(
        name = target_test,
        srcs = [source_name],
        deps = [
            ":%s" % level_3_operation,
            "//randoms/foundation/%s/%s/%s/test_fixtures:%s" % (
                level_1,
                level_2,
                level_3,
                level_3_operation,
            ),
        ],
    )

    return target_test
