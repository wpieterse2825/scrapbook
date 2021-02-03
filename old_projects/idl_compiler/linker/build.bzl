load("@bazel_skylib//rules:common_settings.bzl", "BuildSettingInfo")
load("//:build.bzl", "build_tools")
load(
    "//old_projects/idl_compiler:build_private.bzl",
    "IDLEnumerationInfo",
    "IDLFunctionInfo",
    "IDLHandleInfo",
    "IDLLinkerToolchainInfo",
    "IDLStructureInfo",
)

_EXEC_GROUP_NAME = "idl_linker"
_EXEC_GROUP_TOOLCHAIN = "//old_projects/idl_compiler/linker:toolchain_type"

def _idl_linker_toolchain_impl(ctx):
    return [
        platform_common.ToolchainInfo(
            idl_linker = IDLLinkerToolchainInfo(
                archive = build_tools.get_tool_files(ctx.attr.archive),
            ),
        ),
    ]

idl_linker_toolchain = rule(
    implementation = _idl_linker_toolchain_impl,
    attrs = {
        "archive": build_tools.generate_tool_label(),
    },
    provides = [platform_common.ToolchainInfo],
)

def _get_toolchain(ctx):
    return build_tools.get_exec_group_toolchain(ctx, _EXEC_GROUP_NAME, _EXEC_GROUP_TOOLCHAIN).idl_linker

def _get_toolchain_tool(ctx):
    toolchain = _get_toolchain(ctx)

    return toolchain.archive

def _generate_linking(ctx):
    inputs = []
    outputs = []
    extra_run_arguments = {}

    archive = ctx.actions.declare_file("%s.bin" % ctx.label.name)
    outputs.append(archive)

    deps = ctx.attr.deps
    use_persistent_workers = ctx.attr._use_persistent_workers[BuildSettingInfo].value
    logging_level = ctx.attr._logging_level[BuildSettingInfo].value
    if use_persistent_workers == True:
        arguments_file = ctx.actions.declare_file("%s.args" % ctx.label.name)
        inputs.append(arguments_file)

        arguments_content = ""
        arguments_content += "--output\n%s\n" % archive.path
        arguments_content += "--log_level\n%s\n" % logging_level

        for raw_dep in deps:
            if IDLHandleInfo in raw_dep:
                dep = raw_dep[IDLHandleInfo]

                inputs.append(dep.binary)
                arguments_content += "--input_handle\n%s\n" % dep.binary.path
            elif IDLEnumerationInfo in raw_dep:
                dep = raw_dep[IDLEnumerationInfo]

                inputs.append(dep.binary)
                arguments_content += "--input_enumeration\n%s\n" % dep.binary.path
            elif IDLStructureInfo in raw_dep:
                dep = raw_dep[IDLStructureInfo]

                inputs.append(dep.binary)
                arguments_content += "--input_structure\n%s\n" % dep.binary.path
            elif IDLFunctionInfo in raw_dep:
                dep = raw_dep[IDLFunctionInfo]

                inputs.append(dep.binary)
                arguments_content += "--input_function\n%s\n" % dep.binary.path

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
        arguments.add("--output", archive)
        arguments.add("--log_level", logging_level)

        for raw_dep in deps:
            if IDLHandleInfo in raw_dep:
                dep = raw_dep[IDLHandleInfo]

                inputs.append(dep.binary)
                arguments.add("--input_handle", dep.binary)
            elif IDLEnumerationInfo in raw_dep:
                dep = raw_dep[IDLEnumerationInfo]

                inputs.append(dep.binary)
                arguments.add("--input_enumeration", dep.binary)
            elif IDLStructureInfo in raw_dep:
                dep = raw_dep[IDLStructureInfo]

                inputs.append(dep.binary)
                arguments.add("--input_structure", dep.binary)
            elif IDLFunctionInfo in raw_dep:
                dep = raw_dep[IDLFunctionInfo]

                inputs.append(dep.binary)
                arguments.add("--input_function", dep.binary)

        extra_run_arguments["arguments"] = [
            arguments,
        ]

    linker = _get_toolchain_tool(ctx)

    ctx.actions.run(
        progress_message = "Linking archive %s" % archive.short_path,
        exec_group = _EXEC_GROUP_NAME,
        executable = linker,
        tools = [linker],
        inputs = inputs,
        outputs = outputs,
        **extra_run_arguments
    )

    return archive

def _generate_attributes():
    return {
        "deps": attr.label_list(
            mandatory = True,
            providers = [
                [IDLHandleInfo],
                [IDLEnumerationInfo],
                [IDLStructureInfo],
                [IDLFunctionInfo],
            ],
        ),
        "_use_persistent_workers": attr.label(
            default = Label("//old_projects/idl_compiler/linker/archive:use_persistent_workers"),
            providers = [BuildSettingInfo],
        ),
        "_logging_level": attr.label(
            default = Label("//old_projects/idl_compiler/linker/archive:logging_level"),
            providers = [BuildSettingInfo],
        ),
    }

def _generate_execution_groups():
    return {
        _EXEC_GROUP_NAME: exec_group(
            toolchains = [_EXEC_GROUP_TOOLCHAIN],
        ),
    }

toolchain_tools = struct(
    generate_linking = _generate_linking,
    generate_attributes = _generate_attributes,
    generate_execution_groups = _generate_execution_groups,
)
