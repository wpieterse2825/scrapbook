#
# Copyright 2020 - The World Tree and the The World Tree contributors.
# SPDX-License-Identifier: MIT
#

"""CPU specific C/C++ toolchain features."""

load(
    "@rules_cc//cc:cc_toolchain_config_lib.bzl",
    "feature",
    "flag_group",
    "flag_set",
)
load(
    "@rules_cc//cc:action_names.bzl",
    _ACTION_NAMES = "ACTION_NAMES",
)
load(
    "//asgard/build/toolchains/cpp/features/cpu:arm_aem_v8.bzl",
    _generate_cpu_features_arm_aem_v8 = "generate_cpu_features",
)
load(
    "//asgard/build/toolchains/cpp/features/cpu:qemu_virtual_arm.bzl",
    _generate_cpu_features_qemu_virtual_arm = "generate_cpu_features",
)
load(
    "//asgard/build/toolchains/cpp/features/cpu:qemu_virtual_riscv.bzl",
    _generate_cpu_features_qemu_virtual_riscv = "generate_cpu_features",
)

#
# NOTE: Reason for the below disabling of the 'docstring' is because this is called from the C/C++ toolchain rule implementation, thus it uses the same inputs
# and outputs as the rule implementation.
#
# buildifier: disable=function-docstring
def generate_cpu_features(ctx):
    features = [
        feature(
            name = "processor_arm_64_little",
            flag_sets = [
                flag_set(
                    actions = [
                        _ACTION_NAMES.assemble,
                        _ACTION_NAMES.preprocess_assemble,
                        _ACTION_NAMES.c_compile,
                        _ACTION_NAMES.cpp_link_executable,
                        _ACTION_NAMES.cpp_link_dynamic_library,
                    ],
                    flag_groups = [
                        flag_group(
                            flags = ["--target=aarch64-linux-elf"],
                        ),
                    ],
                ),
            ],
        ),
        feature(
            name = "processor_riscv_64_little",
            flag_sets = [
                flag_set(
                    actions = [
                        _ACTION_NAMES.assemble,
                        _ACTION_NAMES.preprocess_assemble,
                        _ACTION_NAMES.c_compile,
                        _ACTION_NAMES.cpp_link_executable,
                        _ACTION_NAMES.cpp_link_dynamic_library,
                    ],
                    flag_groups = [
                        flag_group(
                            flags = ["--target=riscv64"],
                        ),
                    ],
                ),
            ],
        ),
        feature(
            name = "processor_riscv_64_gc",
            flag_sets = [
                flag_set(
                    actions = [
                        _ACTION_NAMES.assemble,
                        _ACTION_NAMES.preprocess_assemble,
                        _ACTION_NAMES.c_compile,
                        _ACTION_NAMES.cpp_link_executable,
                        _ACTION_NAMES.cpp_link_dynamic_library,
                    ],
                    flag_groups = [
                        flag_group(
                            flags = [
                                "-march=rv64gc",

                                # TODO(wpieterse): LLD is complaing, figure out why if this is disabled.
                                "-mno-relax",
                            ],
                        ),
                    ],
                ),
            ],
            implies = ["processor_riscv_64_little"],
        ),
    ]

    features += _generate_cpu_features_arm_aem_v8(ctx)
    features += _generate_cpu_features_qemu_virtual_arm(ctx)
    features += _generate_cpu_features_qemu_virtual_riscv(ctx)

    return features
