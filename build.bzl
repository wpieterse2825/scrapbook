def _get_exec_group_toolchain(ctx, exec_group, toolchain):
    return ctx.exec_groups[exec_group].toolchains[toolchain]

def _get_tool_files(attr):
    default_info = attr[DefaultInfo]

    return default_info.files_to_run

def _generate_tool_label():
    return attr.label(
        cfg = "target",
        executable = True,
        mandatory = True,
    )

build_tools = struct(
    get_exec_group_toolchain = _get_exec_group_toolchain,
    get_tool_files = _get_tool_files,
    generate_tool_label = _generate_tool_label,
)
