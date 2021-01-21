load("//tools/idl:build_private.bzl", "IDLGeneratorInfo")
load("//tools/idl/generator:build.bzl", "toolchain_tools")

def _idl_generator_c_impl(ctx):
    outputs = []

    header = toolchain_tools.generate_generation(ctx, "c")
    outputs.append(header)

    return [
        DefaultInfo(
            files = depset(outputs),
        ),
        IDLGeneratorInfo(
            generated = [header],
        ),
    ]

idl_generator_c = rule(
    implementation = _idl_generator_c_impl,
    attrs = toolchain_tools.generate_attributes("c"),
    exec_groups = toolchain_tools.generate_execution_groups("c"),
    provides = [
        DefaultInfo,
        IDLGeneratorInfo,
    ],
)
