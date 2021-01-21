#
# Copyright 2020 - The World Tree and the The World Tree contributors.
# SPDX-License-Identifier: MIT
#

"""Toolchain configuration rule for QEmu systems."""

load(
    "//asgard/build/toolchains/qemu:providers.bzl",
    _QemuInfo = "QemuInfo",
)

def _qemu_toolchain_impl(ctx):
    toolchain_info = platform_common.ToolchainInfo(
        qemu = _QemuInfo(
            binary = ctx.attr.binary,
        ),
    )

    return [
        toolchain_info,
    ]

qemu_toolchain = rule(
    implementation = _qemu_toolchain_impl,
    attrs = {
        "binary": attr.label(
            mandatory = True,
            doc = "The QEmu binary to invoke to start the desired system.",
        ),
    },
    doc = "Configures a QEmu system toolchain usable by the Bazel toolchain machinery.",
)
