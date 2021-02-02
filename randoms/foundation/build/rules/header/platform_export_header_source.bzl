load(
    "//randoms/foundation/build/rules:build.bzl",
    _level_3_implementations = "level_3_implementations",
    _level_3_operations = "level_3_operations",
    _level_3_platform_nice_name = "level_3_platform_nice_name",
)

def _platform_export_header_source_impl(ctx):
    level_1 = ctx.attr.level_1
    level_2 = ctx.attr.level_2
    level_3 = ctx.attr.level_3
    level_3_platform = ctx.attr.level_3_platform

    level_1_upper = level_1.upper()
    level_2_upper = level_2.upper()
    level_3_upper = level_3.upper()
    level_3_platform_upper = level_3_platform.upper()

    level_3_platform_nice = _level_3_platform_nice_name(
        level_1 = level_1,
        level_2 = level_2,
        level_3 = level_3,
        level_3_platform = level_3_platform,
    )

    level_3_implementations = _level_3_implementations(
        level_1 = level_1,
        level_2 = level_2,
        level_3 = level_3,
        level_3_platform = level_3_platform,
    )

    level_3_operations = _level_3_operations(
        level_1 = level_1,
        level_2 = level_2,
        level_3 = level_3,
    )

    output_copy_name = "%s.raw" % level_3
    output_file = ctx.actions.declare_file(output_copy_name)
    output_content = ""

    output_content += "#pragma once\n"
    output_content += "\n"

    define_name = ""

    if level_1 == "frameworks":
        define_name = "NM_%s_%s_%s_IMPLEMENTATION" % (
            level_2_upper,
            level_3_upper,
            level_3_platform_upper,
        )
    else:
        define_name = "NM_%s_%s_%s_%s_IMPLEMENTATION" % (
            level_1_upper,
            level_2_upper,
            level_3_upper,
            level_3_platform_upper,
        )

    output_content += "#define %s_UNKNOWN 0\n" % define_name

    for index, (implementation_name, _) in enumerate(level_3_implementations.items()):
        implementation_name_upper = implementation_name.upper()

        output_content += "#define %s_%s %s\n" % (
            define_name,
            implementation_name_upper,
            index + 1,
        )

    output_content += "\n"
    output_content += "#if !defined(%s)\n" % define_name
    output_content += "#error Please define an implementation to use.\n"
    output_content += "#endif\n"
    output_content += "\n"

    for (implementation_name, _) in level_3_implementations.items():
        implementation_name_upper = implementation_name.upper()

        output_content += "#if %s == %s_%s\n" % (
            define_name,
            define_name,
            implementation_name_upper,
        )

        for (operation_name, _) in level_3_operations.items():
            output_content += "#include \"randoms/foundation/%s/%s/%s/%s/%s/%s.hpp\"\n" % (
                level_1,
                level_2,
                level_3,
                level_3_platform,
                implementation_name,
                operation_name,
            )

        output_content += "#endif\n"
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

    for index, (implementation_name, implementation_details) in enumerate(level_3_implementations.items()):
        implementation_name_upper = implementation_name.upper()

        output_content += "#if %s == %s_%s\n" % (
            define_name,
            define_name,
            implementation_name_upper,
        )

        for (_, operation_nice_name) in level_3_operations.items():
            output_content += "   using %s_%s_Export = %s_%s_%s;\n" % (
                operation_nice_name,
                level_3_platform_nice,
                operation_nice_name,
                level_3_platform_nice,
                implementation_details["nice_name"],
            )

        output_content += "#endif\n"

        if index != (len(level_3_implementations) - 1):
            output_content += "\n"

    if level_1 == "frameworks":
        output_content += "} // namespace next_mode::%s::%s::detail {\n" % (
            level_2,
            level_3,
        )
    else:
        output_content += "} // namespace next_mode::%s::%s::%s::detail {\n" % (
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

platform_export_header_source = rule(
    implementation = _platform_export_header_source_impl,
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
    },
)
