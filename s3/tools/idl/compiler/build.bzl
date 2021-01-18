load("@bazel_skylib//rules:common_settings.bzl", "BuildSettingInfo")
load("//tools:build.bzl", "build_tools")
load("//tools/idl:build_private.bzl", "IDLCompilerToolchainInfo")

_EXEC_GROUP_NAME="idl_compiler"
_EXEC_GROUP_TOOLCHAIN="//tools/idl/compiler:toolchain_type"

def _idl_compiler_toolchain_impl(ctx):
    return [
        platform_common.ToolchainInfo(
            idl_compiler = IDLCompilerToolchainInfo(
                handle_compiler = build_tools.get_tool_files(ctx.attr.handle_compiler),
                enumeration_compiler = build_tools.get_tool_files(ctx.attr.enumeration_compiler),
                structure_compiler = build_tools.get_tool_files(ctx.attr.structure_compiler),
                function_compiler = build_tools.get_tool_files(ctx.attr.function_compiler),
            ),
        ),
    ]

idl_compiler_toolchain = rule(
    implementation = _idl_compiler_toolchain_impl,
    attrs = {
        "handle_compiler": build_tools.generate_tool_label(),
        "enumeration_compiler": build_tools.generate_tool_label(),
        "structure_compiler": build_tools.generate_tool_label(),
        "function_compiler": build_tools.generate_tool_label(),
    },
    provides = [platform_common.ToolchainInfo],
)

def _get_toolchain(ctx):
    return build_tools.get_exec_group_toolchain(ctx, _EXEC_GROUP_NAME, _EXEC_GROUP_TOOLCHAIN).idl_compiler

def _get_toolchain_tool(ctx, item_type):
    toolchain = _get_toolchain(ctx)

    if item_type == "handle":
        return toolchain.handle_compiler
    elif item_type == "enumeration":
        return toolchain.enumeration_compiler
    elif item_type == "structure":
        return toolchain.structure_compiler
    elif item_type == "function":
        return toolchain.function_compiler

    # TODO(wpieterse): Fix this!
    fail("ERROR")

def _generate_compilation(ctx, item_type):
    inputs = []
    outputs = []
    extra_run_arguments = {}

    source = ctx.file.src
    inputs.append(source)

    binary = ctx.actions.declare_file("%s.bin" % ctx.label.name)
    outputs.append(binary)

    use_persistent_workers = ctx.attr._use_persistent_workers[BuildSettingInfo].value
    logging_level = ctx.attr._logging_level[BuildSettingInfo].value
    if use_persistent_workers == True:
        arguments_file = ctx.actions.declare_file("%s.args" % ctx.label.name)
        inputs.append(arguments_file)

        arguments_content = ""
        arguments_content += "--input\n%s\n" % source.path
        arguments_content += "--output\n%s\n" % binary.path
        arguments_content += "--log_level\n%s\n" % logging_level

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
        arguments.add("--input", source)
        arguments.add("--output", binary)
        arguments.add("--log_level", logging_level)

        extra_run_arguments["arguments"] = [
            arguments,
        ]

    compiler = _get_toolchain_tool(ctx, item_type)

    ctx.actions.run(
        progress_message = "Compiling %s %s" % (
            item_type,
            binary.short_path,
        ),
        exec_group = _EXEC_GROUP_NAME,
        executable = compiler,
        tools = [compiler],
        inputs = inputs,
        outputs = outputs,
        **extra_run_arguments
    )

    return binary

def _generate_attributes(item_type):
    return {
        "src": attr.label(
            mandatory = True,
            allow_single_file = [".yaml"],
        ),
        "_use_persistent_workers": attr.label(
            default = Label("//tools/idl/compiler/%s:use_persistent_workers" % item_type),
            providers = [BuildSettingInfo],
        ),
        "_logging_level": attr.label(
            default = Label("//tools/idl/compiler/%s:logging_level" % item_type),
            providers = [BuildSettingInfo],
        ),
    }

def _generate_execution_groups(item_type):
    return {
        _EXEC_GROUP_NAME: exec_group(
            toolchains = [_EXEC_GROUP_TOOLCHAIN],
        ),
    }

toolchain_tools = struct(
    generate_compilation = _generate_compilation,
    generate_attributes = _generate_attributes,
    generate_execution_groups = _generate_execution_groups,
)
