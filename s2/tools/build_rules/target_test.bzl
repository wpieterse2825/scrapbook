load("@rules_cc//cc:defs.bzl", "cc_test")

_EXEC_GROUP_HOST_TOOLS = "host_tools"

def _target_test_transition_impl(settings, attr):
    _ignore = (settings, attr)

    return {}

_target_test_transition = transition(
    implementation = _target_test_transition_impl,
    inputs = [],
    outputs = [],
)

def _target_test_impl(ctx):
    host_tools_exec_group = ctx.exec_groups[_EXEC_GROUP_HOST_TOOLS]
    host_tools_toolchain_collection = host_tools_exec_group.toolchains["//tools/host:toolchain_type"]
    host_tools_toolchain = host_tools_toolchain_collection.host_tools

    executable_src = ctx.executable.native_binary
    executable_dst = ctx.actions.declare_file(ctx.label.name)

    runfiles = ctx.attr.native_binary[0][DefaultInfo].default_runfiles

    copy_arguments = ctx.actions.args()
    copy_arguments.add("--input", executable_src)
    copy_arguments.add("--output", executable_dst)

    ctx.actions.run(
        inputs = [executable_src],
        outputs = [executable_dst],
        exec_group = _EXEC_GROUP_HOST_TOOLS,
        executable = host_tools_toolchain.copy,
        arguments = [copy_arguments],
        tools = [host_tools_toolchain.copy],
    )

    return [
        DefaultInfo(
            executable = executable_dst,
            runfiles = runfiles,
        ),
    ]

_target_test = rule(
    implementation = _target_test_impl,
    test = True,
    attrs = {
        "native_binary": attr.label(
            cfg = _target_test_transition,
            executable = True,
        ),
        "_whitelist_function_transition": attr.label(
            default = "@bazel_tools//tools/whitelists/function_transition_whitelist",
        ),
    },
    exec_groups = {
        _EXEC_GROUP_HOST_TOOLS: exec_group(
            toolchains = [
                "//tools/host:toolchain_type",
            ],
        ),
    },
)

def target_test(name, **kwargs):
    native_test_name = name + "_native_test"

    cc_test(
        name = native_test_name,
        **kwargs,
    )

    _target_test(
        name = name,
        native_binary = ":%s" % native_test_name,
    )
