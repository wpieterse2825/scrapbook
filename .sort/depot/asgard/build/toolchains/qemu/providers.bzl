#
# Copyright 2020 - The World Tree and the The World Tree contributors.
# SPDX-License-Identifier: MIT
#

"""Bazel providers returned by the QEmu toolchain rules."""

QemuInfo = provider(
    doc = "Provides information about the selected QEmu toolchain.",
    fields = {
        "binary": "The QEmu binary to invoke to run the selected system.",
    },
)
