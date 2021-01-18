#
# Copyright 2020 - The World Tree and the The World Tree contributors.
# SPDX-License-Identifier: MIT
#

"""GPU specific C/C++ toolchain features."""

#
# NOTE: Reason for the below disabling of the 'docstring' is because this is called from the C/C++ toolchain rule implementation, thus it uses the same inputs
# and outputs as the rule implementation.
#
# buildifier: disable=function-docstring
def generate_gpu_features(ctx):
    features = []

    return features
