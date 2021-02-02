load("//randoms/foundation/build/rules/cpp:cpp_binary.bzl", _cpp_binary = "cpp_binary")
load(
    "//randoms/foundation/build/rules/bench:bench_source.bzl",
    _bench_source = "bench_source",
    _bench_source_name = "bench_source_name",
)

def bench(
        name,
        level_1,
        level_2,
        level_3,
        level_3_platform,
        level_3_implementation,
        level_3_operation):
    target_generated = "_bench_generated_%s" % level_3_operation
    target_copy = "_bench_copy_%s" % level_3_operation
    target_bench = "bench_%s" % level_3_operation
    source_name = "%s.cpp" % _bench_source_name(level_3_operation = level_3_operation)

    _bench_source(
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

    _cpp_binary(
        name = target_bench,
        srcs = [source_name],
        deps = [
            ":%s" % level_3_operation,
            "//randoms/foundation/%s/%s/%s/bench_fixtures:%s" % (
                level_1,
                level_2,
                level_3,
                level_3_operation,
            ),
        ],
    )

    return target_bench
