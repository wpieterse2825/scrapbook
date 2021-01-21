load("//tools/idl:build_private.bzl", "IDLEnumerationInfo")
load("//tools/idl/compiler:build.bzl", "toolchain_tools")

def _idl_enumeration_impl(ctx):
    outputs = []

    binary = toolchain_tools.generate_compilation(ctx, "enumeration")
    outputs.append(binary)

    return [
        DefaultInfo(
            files = depset(outputs),
        ),
        IDLEnumerationInfo(
            binary = binary,
        ),
    ]

idl_enumeration = rule(
    implementation = _idl_enumeration_impl,
    attrs = toolchain_tools.generate_attributes("enumeration"),
    exec_groups = toolchain_tools.generate_execution_groups("enumeration"),
    provides = [
        DefaultInfo,
        IDLEnumerationInfo,
    ],
)
