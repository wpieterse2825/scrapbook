load("//tools/idl:build_private.bzl", "IDLHandleInfo")
load("//tools/idl/compiler:build.bzl", "toolchain_tools")

def _idl_handle_impl(ctx):
    outputs = []

    binary = toolchain_tools.generate_compilation(ctx, "handle")
    outputs.append(binary)

    return [
        DefaultInfo(
            files = depset(outputs),
        ),
        IDLHandleInfo(
            binary = binary,
        ),
    ]

idl_handle = rule(
    implementation = _idl_handle_impl,
    attrs = toolchain_tools.generate_attributes("handle"),
    exec_groups = toolchain_tools.generate_execution_groups("handle"),
    provides = [
        DefaultInfo,
        IDLHandleInfo,
    ],
)
