load("//old_projects/idl_compiler:build_private.bzl", "IDLArchiveInfo")
load("//old_projects/idl_compiler/linker:build.bzl", "toolchain_tools")

def _idl_archive_impl(ctx):
    outputs = []

    archive = toolchain_tools.generate_linking(ctx)
    outputs.append(archive)

    return [
        DefaultInfo(
            files = depset(outputs),
        ),
        IDLArchiveInfo(
            binary = archive,
        ),
    ]

idl_archive = rule(
    implementation = _idl_archive_impl,
    attrs = toolchain_tools.generate_attributes(),
    exec_groups = toolchain_tools.generate_execution_groups(),
    provides = [
        DefaultInfo,
        IDLArchiveInfo,
    ],
)