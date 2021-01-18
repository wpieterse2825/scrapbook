#
# Copyright 2020 - The World Tree and the The World Tree contributors.
# SPDX-License-Identifier: MIT
#

"""C/C++ toolchain configuration rules."""

load(
    "//asgard/build/toolchains/cpp/features:base.bzl",
    _generate_base_features = "generate_base_features",
)
load(
    "//asgard/build/toolchains/cpp/features:cpu.bzl",
    _generate_cpu_features = "generate_cpu_features",
)
load(
    "//asgard/build/toolchains/cpp/features:gpu.bzl",
    _generate_gpu_features = "generate_gpu_features",
)
load(
    "//asgard/build/toolchains/cpp/actions:base.bzl",
    _generate_base_actions = "generate_base_actions",
)

def _cc_toolchain_configuration_impl(ctx):
    features = []
    features += _generate_base_features(ctx)
    features += _generate_cpu_features(ctx)
    features += _generate_gpu_features(ctx)

    actions = []
    actions += _generate_base_actions(ctx)

    return [
        cc_common.create_cc_toolchain_config_info(
            ctx = ctx,
            features = features,
            action_configs = actions,
            toolchain_identifier = ctx.attr.toolchain_identifier,
            host_system_name = "k8",
            target_system_name = "the_world_tree",
            target_cpu = "{processor}_{bit_width}_{endianess}".format(
                processor = ctx.attr.processor,
                bit_width = ctx.attr.bit_width,
                endianess = ctx.attr.endianess,
            ),
            target_libc = "none",
            compiler = "clang",
            abi_version = "clang",
            abi_libc_version = "clang",
        ),
    ]

cc_toolchain_configuration = rule(
    implementation = _cc_toolchain_configuration_impl,
    provides = [CcToolchainConfigInfo],
    attrs = {
        "toolchain_identifier": attr.string(
            mandatory = True,
            doc = "The identifier of the C/C++ toolchain used by the Bazel machinery.",
        ),
        "processor": attr.string(
            mandatory = True,
            doc = "The target processor's name.",
        ),
        "bit_width": attr.string(
            mandatory = True,
            doc = "The target processor's bit-width.",
        ),
        "endianess": attr.string(
            mandatory = True,
            doc = "The target processor's endianess.",
        ),
        "extra_features": attr.string_list(
            mandatory = False,
            doc = "Enable these features for all targets that depend on this toolchain.",
        ),
    },
    doc = "Configures the actions of the C/C++ toolchain within Bazel.",
)
