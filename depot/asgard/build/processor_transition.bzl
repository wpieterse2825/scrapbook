#
# Copyright 2020 - The World Tree and the The World Tree contributors.
# SPDX-License-Identifier: MIT
#

"""Rule to transition to a specific processor."""

def _processor_transition_impl(settings, attrs):
    platform_string = "@{workspace_name}//{package_name}:{name}".format(
        workspace_name = attrs.processor.workspace_name,
        package_name = attrs.processor.package,
        name = attrs.processor.name,
    )

    return {
        "//command_line_option:platforms": platform_string,
    }

processor_transition = transition(
    implementation = _processor_transition_impl,
    inputs = [],
    outputs = ["//command_line_option:platforms"],
)
