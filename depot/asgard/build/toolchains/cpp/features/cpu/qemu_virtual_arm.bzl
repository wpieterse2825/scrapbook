#
# Copyright 2020 - The World Tree and the The World Tree contributors.
# SPDX-License-Identifier: MIT
#

"""C/C++ toolchain features specific to the QEmu Virtual ARM processor."""

load(
    "@rules_cc//cc:cc_toolchain_config_lib.bzl",
    _feature = "feature",
)

#
# NOTE: Reason for the below disabling of the 'docstring' is because this is called from the C/C++ toolchain rule implementation, thus it uses the same inputs
# and outputs as the rule implementation.
#
# buildifier: disable=function-docstring
def generate_cpu_features(ctx):
    features = [
        _feature(
            name = "processor_qemu_virtual_arm_64_little",
            implies = ["processor_arm_64_little"],
        ),
    ]

    return features
