load(
    "//old_projects/foundation/build/rules:build.bzl",
    _level_3_implementation_nice_name = "level_3_implementation_nice_name",
    _level_3_operation_nice_name = "level_3_operation_nice_name",
    _level_3_platform_nice_name = "level_3_platform_nice_name",
)

def _empty_operation_header_source_impl(ctx):
    level_1 = ctx.attr.level_1
    level_2 = ctx.attr.level_2
    level_3 = ctx.attr.level_3
    level_3_platform = ctx.attr.level_3_platform
    level_3_implementation = ctx.attr.level_3_implementation
    level_3_operation = ctx.attr.level_3_operation
    level_3_dependent_platform = ctx.attr.level_3_dependent_platform
    level_3_dependent_implementation = ctx.attr.level_3_dependent_implementation

    level_3_platform_nice = _level_3_platform_nice_name(
        level_1 = level_1,
        level_2 = level_2,
        level_3 = level_3,
        level_3_platform = level_3_platform,
    )

    level_3_implementation_nice = _level_3_implementation_nice_name(
        level_1 = level_1,
        level_2 = level_2,
        level_3 = level_3,
        level_3_platform = level_3_platform,
        level_3_implementation = level_3_implementation,
    )

    level_3_operation_nice = _level_3_operation_nice_name(
        level_1 = level_1,
        level_2 = level_2,
        level_3 = level_3,
        level_3_operation = level_3_operation,
    )

    level_3_dependent_platform_nice = _level_3_platform_nice_name(
        level_1 = level_1,
        level_2 = level_2,
        level_3 = level_3,
        level_3_platform = level_3_dependent_platform,
    )

    level_3_dependent_implementation_nice = _level_3_implementation_nice_name(
        level_1 = level_1,
        level_2 = level_2,
        level_3 = level_3,
        level_3_platform = level_3_dependent_platform,
        level_3_implementation = level_3_dependent_implementation,
    )

    output_copy_name = "%s.raw" % level_3_operation
    output_file = ctx.actions.declare_file(output_copy_name)
    output_content = ""

    output_content += "#pragma once\n"
    output_content += "\n"
    output_content += "#include \"randoms/foundation/%s/%s/%s/%s/%s/%s.hpp\"\n" % (
        level_1,
        level_2,
        level_3,
        level_3_dependent_platform,
        level_3_dependent_implementation,
        level_3_operation,
    )

    output_content += "\n"

    if level_1 == "frameworks":
        output_content += "namespace next_mode::%s::%s::detail {\n" % (
            level_2,
            level_3,
        )
    else:
        output_content += "namespace next_mode::%s::%s::%s::detail {\n" % (
            level_1,
            level_2,
            level_3,
        )

    output_content += "    struct %s_%s_%s : public %s_%s_%s {\n" % (
        level_3_operation_nice,
        level_3_platform_nice,
        level_3_implementation_nice,
        level_3_operation_nice,
        level_3_dependent_platform_nice,
        level_3_dependent_implementation_nice,
    )

    output_content += "        using Super = %s_%s_%s;\n" % (
        level_3_operation_nice,
        level_3_dependent_platform_nice,
        level_3_dependent_implementation_nice,
    )

    output_content += "    };\n"

    if level_1 == "frameworks":
        output_content += "} // namespace next_mode::%s::%s::detail\n" % (
            level_2,
            level_3,
        )
    else:
        output_content += "} // namespace next_mode::%s::%s::%s::detail\n" % (
            level_1,
            level_2,
            level_3,
        )

    ctx.actions.write(
        output = output_file,
        content = output_content,
        is_executable = False,
    )

    # TODO(wpieterse): Format the output file with clang-format.

    outputs = [output_file]
    outputs_depset = depset(outputs)

    return [
        DefaultInfo(files = outputs_depset),
    ]

empty_operation_header_source = rule(
    implementation = _empty_operation_header_source_impl,
    attrs = {
        "level_1": attr.string(
            mandatory = True,
        ),
        "level_2": attr.string(
            mandatory = True,
        ),
        "level_3": attr.string(
            mandatory = True,
        ),
        "level_3_platform": attr.string(
            mandatory = True,
        ),
        "level_3_operation": attr.string(
            mandatory = True,
        ),
        "level_3_implementation": attr.string(
            mandatory = True,
        ),
        "level_3_dependent_platform": attr.string(
            mandatory = True,
        ),
        "level_3_dependent_implementation": attr.string(
            mandatory = True,
        ),
    },
)
