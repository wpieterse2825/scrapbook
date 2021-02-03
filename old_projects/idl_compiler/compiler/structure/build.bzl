load("//old_projects/idl_compiler:build_private.bzl", "IDLStructureInfo")
load("//old_projects/idl_compiler/compiler:build.bzl", "toolchain_tools")

def _idl_structure_impl(ctx):
    outputs = []

    binary = toolchain_tools.generate_compilation(ctx, "structure")
    outputs.append(binary)

    return [
        DefaultInfo(
            files = depset(outputs),
        ),
        IDLStructureInfo(
            binary = binary,
        ),
    ]

idl_structure = rule(
    implementation = _idl_structure_impl,
    attrs = toolchain_tools.generate_attributes("structure"),
    exec_groups = toolchain_tools.generate_execution_groups("structure"),
    provides = [
        DefaultInfo,
        IDLStructureInfo,
    ],
)
