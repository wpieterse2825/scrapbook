load("//old_projects/idl_compiler:build_private.bzl", "IDLFunctionInfo")
load("//old_projects/idl_compiler/compiler:build.bzl", "toolchain_tools")

def _idl_function_impl(ctx):
    outputs = []

    binary = toolchain_tools.generate_compilation(ctx, "function")
    outputs.append(binary)

    return [
        DefaultInfo(
            files = depset(outputs),
        ),
        IDLFunctionInfo(
            binary = binary,
        ),
    ]

idl_function = rule(
    implementation = _idl_function_impl,
    attrs = toolchain_tools.generate_attributes("function"),
    exec_groups = toolchain_tools.generate_execution_groups("function"),
    provides = [
        DefaultInfo,
        IDLFunctionInfo,
    ],
)
