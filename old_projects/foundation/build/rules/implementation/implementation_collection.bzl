load(
    "//old_projects/foundation/build/rules:build.bzl",
    _level_3_operation_names = "level_3_operations",
    _level_3_visibility = "level_3_visibility",
)
load("//old_projects/foundation/build/rules/cpp:cpp_library.bzl", _cpp_library = "cpp_library")
load("//old_projects/foundation/build/rules/header:empty_operation_header.bzl", _empty_operation_header = "empty_operation_header")
load("//old_projects/foundation/build/rules/test:test.bzl", _test = "test")
load("//old_projects/foundation/build/rules/bench:bench.bzl", _bench = "bench")

def implementation_collection(
        name,
        level_1,
        level_2,
        level_3,
        level_3_platform,
        level_3_implementation,
        level_3_dependent_platform = "",
        level_3_dependent_implementation = ""):
    operation_names = _level_3_operation_names(
        level_1 = level_1,
        level_2 = level_2,
        level_3 = level_3,
    )

    available_headers = native.glob(include = ["*.hpp"])

    for operation_name in operation_names:
        found = False
        for header in available_headers:
            header_base_name = header[:-4]

            if operation_name == header_base_name:
                found = True

        if found == False:
            if level_3_dependent_platform == "" and level_3_dependent_implementation == "":
                fail(
                    "The common implementation at //old_projects/foundation/%s/%s/%s does not define a header for the %s operation!" % (
                        level_1,
                        level_2,
                        level_3,
                        operation_name,
                    ),
                )

            _empty_operation_header(
                name = name,
                level_1 = level_1,
                level_2 = level_2,
                level_3 = level_3,
                level_3_platform = level_3_platform,
                level_3_implementation = level_3_implementation,
                level_3_operation = operation_name,
                level_3_dependent_platform = level_3_dependent_platform,
                level_3_dependent_implementation = level_3_dependent_implementation,
            )

    base_path = "//old_projects/foundation/%s/%s/%s" % (
        level_1,
        level_2,
        level_3,
    )

    for operation_name in operation_names:
        operation_dependencies = []

        operation_dependencies.append("%s:internal" % base_path)
        if level_3_dependent_platform != "" and level_3_dependent_implementation != "":
            depends_on_path = "%s/%s/%s" % (
                base_path,
                level_3_dependent_platform,
                level_3_dependent_implementation,
            )

            operation_dependencies.append(
                "%s:%s" % (
                    depends_on_path,
                    operation_name,
                ),
            )

        _cpp_library(
            name = operation_name,
            hdrs = ["%s.hpp" % operation_name],
            visibility = _level_3_visibility(
                level_1 = level_1,
                level_2 = level_2,
                level_3 = level_3,
            ),
            deps = operation_dependencies,
        )

    test_collection = []
    bench_collection = []

    for operation_name in operation_names:
        found = False
        for header in available_headers:
            header_base_name = header[:-4]

            if operation_name == header_base_name:
                found = True

        if found == True:
            current_test = _test(
                name = name,
                level_1 = level_1,
                level_2 = level_2,
                level_3 = level_3,
                level_3_platform = level_3_platform,
                level_3_implementation = level_3_implementation,
                level_3_operation = operation_name,
            )

            test_collection.append(current_test)

            current_bench = _bench(
                name = name,
                level_1 = level_1,
                level_2 = level_2,
                level_3 = level_3,
                level_3_platform = level_3_platform,
                level_3_implementation = level_3_implementation,
                level_3_operation = operation_name,
            )

            bench_collection.append(current_bench)

    if len(test_collection) != 0:
        native.test_suite(
            name = name,
            tests = test_collection,
        )
