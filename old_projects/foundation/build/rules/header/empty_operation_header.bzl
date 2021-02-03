load("//old_projects/foundation/build/rules/header:empty_operation_header_source.bzl", _empty_operation_header_source = "empty_operation_header_source")

def empty_operation_header(
        name,
        level_1,
        level_2,
        level_3,
        level_3_platform,
        level_3_implementation,
        level_3_operation,
        level_3_dependent_platform,
        level_3_dependent_implementation):
    generated_name = "_empty_operation_header_generated_%s" % level_3_operation
    copy_name = "_empty_operation_header_copy_%s" % level_3_operation
    header_name = "%s.hpp" % level_3_operation

    _empty_operation_header_source(
        name = generated_name,
        level_1 = level_1,
        level_2 = level_2,
        level_3 = level_3,
        level_3_platform = level_3_platform,
        level_3_implementation = level_3_implementation,
        level_3_operation = level_3_operation,
        level_3_dependent_platform = level_3_dependent_platform,
        level_3_dependent_implementation = level_3_dependent_implementation,
    )

    native.genrule(
        name = copy_name,
        srcs = [":%s" % generated_name],
        outs = [header_name],
        cmd = "cp $(SRCS) $@",
    )
