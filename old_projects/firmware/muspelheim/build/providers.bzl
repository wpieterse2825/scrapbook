#
# Copyright 2020 - The World Tree and the The World Tree contributors.
# SPDX-License-Identifier: MIT
#

"""Muspelheim rule providers."""

FlashImageOverlayInfo = provider(
    doc = "Provides details about a firmware image that is an overlay of other firmware images.",
    fields = {
    },
)

FlashImageInfo = provider(
    doc = "Provides details about a firmware image.",
    fields = {
    },
)

FlashRegionInfo = provider(
    doc = "Provides details about a firmware region.",
    fields = {
    },
)

FlashPartitionInfo = provider(
    doc = "Provides details about a firmware partition.",
    fields = {
    },
)

FlashFileInfo = provider(
    doc = "Provides details about a firmware file section.",
    fields = {
        "identifier": "The 4-character name of this file on a flash partition.",
        "binary": "The File instance that points to the generated binary which is based on the input data.",
        "metadata": "The File instance that points to the generated metadata for the input data.",
    },
)
