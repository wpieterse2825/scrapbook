HostToolsInfo = provider(
    fields = [
        "copy",
    ],
)

def _host_tools_toolchain_impl(ctx):
    return [
        platform_common.ToolchainInfo(
            host_tools = HostToolsInfo(
                copy = ctx.executable.copy,
            ),
        ),
    ]

host_tools_toolchain = rule(
    implementation = _host_tools_toolchain_impl,
    attrs = {
        "copy": attr.label(
            cfg = "exec",
            mandatory = True,
            executable = True,
        ),
    },
)
