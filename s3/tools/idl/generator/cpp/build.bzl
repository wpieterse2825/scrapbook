load("//tools/idl:build_private.bzl", "IDLGeneratorInfo")
load("//tools/idl/generator:build.bzl", "toolchain_tools")

def _idl_generator_cpp_impl(ctx):
    outputs = []

    header = toolchain_tools.generate_generation(ctx, "cpp")
    outputs.append(header)

    return [
        DefaultInfo(
            files = depset(outputs),
        ),
        IDLGeneratorInfo(
            generated = [header],
        ),
    ]

idl_generator_cpp = rule(
    implementation = _idl_generator_cpp_impl,
    attrs = toolchain_tools.generate_attributes("c"),
    exec_groups = toolchain_tools.generate_execution_groups("cpp"),
    provides = [
        DefaultInfo,
        IDLGeneratorInfo,
    ],
)
