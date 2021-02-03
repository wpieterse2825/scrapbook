load("@bazel_skylib//rules:common_settings.bzl", "BuildSettingInfo")
load("//:build.bzl", "build_tools")
load(
    "//old_projects/idl_compiler:build_private.bzl",
    "IDLArchiveInfo",
    "IDLGeneratorPropertiesInfo",
    "IDLGeneratorToolchainInfo",
)

_EXEC_GROUP_NAME = "idl_generator"
_EXEC_GROUP_TOOLCHAIN = "//old_projects/idl_compiler/generator:toolchain_type"

def _idl_generator_toolchain_impl(ctx):
    return [
        platform_common.ToolchainInfo(
            idl_generator = IDLGeneratorToolchainInfo(
                generator_c = build_tools.get_tool_files(ctx.attr.generator_c),
                generator_cpp = build_tools.get_tool_files(ctx.attr.generator_cpp),
            ),
        ),
    ]

idl_generator_toolchain = rule(
    implementation = _idl_generator_toolchain_impl,
    attrs = {
        "generator_c": build_tools.generate_tool_label(),
        "generator_cpp": build_tools.generate_tool_label(),
    },
    provides = [platform_common.ToolchainInfo],
)

def _get_toolchain(ctx):
    return build_tools.get_exec_group_toolchain(ctx, _EXEC_GROUP_NAME, _EXEC_GROUP_TOOLCHAIN).idl_generator

def _get_toolchain_tool(ctx, language_type):
    toolchain = _get_toolchain(ctx)

    if language_type == "c":
        return toolchain.generator_c
    elif language_type == "cpp":
        return toolchain.generator_cpp

    # TODO(wpieterse): Fix this!
    fail("ERROR")

def _generate_generation(ctx, language_type):
    inputs = []
    outputs = []
    extra_run_arguments = {}

    binary = ctx.attr.dep[IDLArchiveInfo].binary
    inputs.append(binary)

    header = None
    if language_type == "c":
        header = ctx.actions.declare_file("%s.h" % ctx.label.name)
    elif language_type == "cpp":
        header = ctx.actions.declare_file("%s.hpp" % ctx.label.name)

    outputs.append(header)

    use_persistent_workers = ctx.attr._use_persistent_workers[BuildSettingInfo].value
    logging_level = ctx.attr._logging_level[BuildSettingInfo].value
    if use_persistent_workers == True:
        arguments_file = ctx.actions.declare_file("%s.args" % ctx.label.name)
        inputs.append(arguments_file)

        arguments_content = ""
        arguments_content += "--input\n%s\n" % binary.path
        arguments_content += "--output\n%s\n" % header.path
        arguments_content += "--log_level\n%s\n" % logging_level

        if ctx.attr.props != None:
            props = ctx.attr.props[IDLGeneratorPropertiesInfo]

            arguments_content += "--handle_prefix\n%s\n" % props.handle_prefix
            arguments_content += "--enumeration_prefix\n%s\n" % props.enumeration_prefix
            arguments_content += "--enumeration_item_prefix\n%s\n" % props.enumeration_item_prefix
            arguments_content += "--structure_prefix\n%s\n" % props.structure_prefix
            arguments_content += "--function_prefix\n%s\n" % props.function_prefix

        ctx.actions.write(
            output = arguments_file,
            content = arguments_content,
        )

        extra_run_arguments["arguments"] = [
            "@%s" % arguments_file.path,
        ]

        extra_run_arguments["execution_requirements"] = {
            "supports-workers": "1",
        }
    else:
        arguments = ctx.actions.args()
        arguments.use_param_file("@%s")
        arguments.set_param_file_format("shell")
        arguments.add("--input", binary)
        arguments.add("--output", header)
        arguments.add("--log_level", logging_level)

        if ctx.attr.props != None:
            props = ctx.attr.props[IDLGeneratorPropertiesInfo]

            arguments.add("--handle_prefix", props.handle_prefix)
            arguments.add("--enumeration_prefix", props.enumeration_prefix)
            arguments.add("--enumeration_item_prefix", props.enumeration_item_prefix)
            arguments.add("--structure_prefix", props.structure_prefix)
            arguments.add("--function_prefix", props.function_prefix)

        extra_run_arguments["arguments"] = [
            arguments,
        ]

    generator = _get_toolchain_tool(ctx, language_type)

    nice_name=""
    if language_type == "c":
        nice_name="C"
    elif language_type == "cpp":
        nice_name="C++"

    ctx.actions.run(
        progress_message = "Generating %s header %s" % (
            nice_name,
            header.short_path,
        ),
        exec_group = _EXEC_GROUP_NAME,
        executable = generator,
        tools = [generator],
        inputs = inputs,
        outputs = outputs,
        **extra_run_arguments
    )

    return header

def _generate_attributes(language_type):
    return {
        "dep": attr.label(
            mandatory = True,
            providers = [IDLArchiveInfo],
        ),
        "props": attr.label(
            providers = [IDLGeneratorPropertiesInfo],
        ),
        "_use_persistent_workers": attr.label(
            default = Label("//old_projects/idl_compiler/generator/%s:use_persistent_workers" % language_type),
            providers = [BuildSettingInfo],
        ),
        "_logging_level": attr.label(
            default = Label("//old_projects/idl_compiler/generator/%s:logging_level" % language_type),
            providers = [BuildSettingInfo],
        ),
    }

def _generate_execution_groups(language_type):
    return {
        _EXEC_GROUP_NAME: exec_group(
            toolchains = [_EXEC_GROUP_TOOLCHAIN],
        ),
    }

toolchain_tools = struct(
    generate_generation = _generate_generation,
    generate_attributes = _generate_attributes,
    generate_execution_groups = _generate_execution_groups,
)
