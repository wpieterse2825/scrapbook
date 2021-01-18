#
# Copyright 2020 - The World Tree and the The World Tree contributors.
# SPDX-License-Identifier: MIT
#

"""Firmware file and file-system related rule definitions."""

load(
    "//asgard/build:processor_transition.bzl",
    "processor_transition",
)
load(
    "//muspelheim/build:providers.bzl",
    "FlashFileInfo",
    "FlashImageInfo",
    "FlashImageOverlayInfo",
    "FlashPartitionInfo",
    "FlashRegionInfo",
)

def _flash_image_overlay_impl(ctx):
    return [
        DefaultInfo(
        ),
        OutputGroupInfo(
        ),
        FlashImageInfo(
        ),
        FlashImageOverlayInfo(
        ),
    ]

flash_image_overlay = rule(
    implementation = _flash_image_overlay_impl,
    provides = [
        DefaultInfo,
        OutputGroupInfo,
        FlashImageInfo,
        FlashImageOverlayInfo,
    ],
    attrs = {
        "flash_images": attr.label_list(
            mandatory = True,
            providers = [
                FlashImageInfo,
            ],
            doc = "A list of flash images to combine into one flash image, where each partition in the image is unique.",
        ),
        "_image_overlay_compiler": attr.label(
            cfg = "exec",
            executable = True,
            default = Label("//muspelheim/tools/firmware/image_overlay_compiler"),
        ),
    },
    doc = "Generates a combined flash image, where each passed in flash image is written to a single image.",
)

def _flash_image_impl(ctx):
    return [
        DefaultInfo(
        ),
        OutputGroupInfo(
        ),
        FlashImageInfo(
        ),
    ]

flash_image = rule(
    implementation = _flash_image_impl,
    provides = [
        DefaultInfo,
        OutputGroupInfo,
        FlashImageInfo,
    ],
    attrs = {
        "regions": attr.label_list(
            mandatory = True,
            providers = [
                FlashRegionInfo,
            ],
            doc = "A list of flash regions that contains code and/or data.",
        ),
        "_image_compiler": attr.label(
            cfg = "exec",
            executable = True,
            default = Label("//muspelheim/tools/firmware/image_compiler"),
        ),
    },
    doc = "Builds a final flash image that can be written to the target device's flash storage.",
)

def _flash_region_impl(ctx):
    return [
        DefaultInfo(
        ),
        OutputGroupInfo(
        ),
        FlashRegionInfo(
        ),
    ]

flash_region = rule(
    implementation = _flash_region_impl,
    provides = [
        DefaultInfo,
        OutputGroupInfo,
        FlashRegionInfo,
    ],
    attrs = {
        "identifier": attr.string(
            mandatory = True,
            doc = "The 4-character name of this region inside the flash image.",
        ),
        "partitions": attr.label_list(
            mandatory = True,
            providers = [
                FlashPartitionInfo,
            ],
            doc = "A list of firmware partitions to combine into this region.",
        ),
        "_region_compiler": attr.label(
            cfg = "exec",
            executable = True,
            default = Label("//muspelheim/tools/firmware/region_compiler"),
        ),
    },
    doc = "Combines a list of flash partitions into a single flash region.",
)

def _flash_partition_impl(ctx):
    return [
        DefaultInfo(
        ),
        OutputGroupInfo(
        ),
        FlashPartitionInfo(
        ),
    ]

flash_partition = rule(
    implementation = _flash_partition_impl,
    provides = [
        DefaultInfo,
        OutputGroupInfo,
        FlashPartitionInfo,
    ],
    attrs = {
        "identifier": attr.string(
            mandatory = True,
            doc = "The 4-character name of this partition inside the flash region.",
        ),
        "files": attr.label_list(
            mandatory = True,
            providers = [
                FlashFileInfo,
            ],
            doc = "A list of firmware files to be added to this partition.",
        ),
        "_partition_compiler": attr.label(
            cfg = "exec",
            executable = True,
            default = Label("//muspelheim/tools/firmware/partition_compiler"),
        ),
    },
    doc = "Combines a list of flash files into a single flash partition.",
)

def _flash_file_code_impl(ctx):
    input_binary = ctx.executable.binary

    output_binary = ctx.actions.declare_file("%s.bin" % ctx.label.name)
    output_metadata = ctx.actions.declare_file("%s.met" % ctx.label.name)

    ctx.actions.run(
        progress_message = "Building flash file %s" % output_binary.short_path,
        executable = ctx.executable._file_compiler,
        arguments = [
            "--input",
            input_binary.path,
            "--output_binary",
            output_binary.path,
            "--output_metadata",
            output_binary.path,
        ],
        inputs = [input_binary],
        outputs = [
            output_binary,
            output_metadata,
        ],
    )

    outputs = [
        output_binary,
        output_metadata,
    ]

    return [
        DefaultInfo(
            files = depset(outputs),
        ),
        OutputGroupInfo(
            all_files = depset(outputs),
        ),
        FlashFileInfo(
            identifier = ctx.attr.identifier,
            binary = output_binary,
            metadata = output_metadata,
        ),
    ]

flash_file_code = rule(
    implementation = _flash_file_code_impl,
    provides = [
        DefaultInfo,
        OutputGroupInfo,
        FlashFileInfo,
    ],
    attrs = {
        "binary": attr.label(
            cfg = processor_transition,
            executable = True,
            mandatory = True,
            doc = "The binary executable target that this image is composed of, which is transitioned to the processor.",
        ),
        "identifier": attr.string(
            mandatory = True,
            doc = "The 16-character identifier of this file inside the flash partition.",
        ),
        "processor": attr.label(
            mandatory = True,
            doc = "The processor this image will execute on.",
        ),
        "_file_compiler": attr.label(
            cfg = "exec",
            executable = True,
            default = Label("//muspelheim/tools/firmware/file_code_compiler"),
        ),
        "_whitelist_function_transition": attr.label(
            default = "@bazel_tools//tools/whitelists/function_transition_whitelist",
        ),
    },
    doc = "A binary file for a specific target platform inside a flash partition.",
)
