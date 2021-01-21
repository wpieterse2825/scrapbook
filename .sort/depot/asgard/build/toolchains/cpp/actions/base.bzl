#
# Copyright 2020 - The World Tree and the The World Tree contributors.
# SPDX-License-Identifier: MIT
#

"""Configure the build actions for the C/C++ toolchain."""

load(
    "@rules_cc//cc:cc_toolchain_config_lib.bzl",
    _action_config = "action_config",
    _tool = "tool",
)
load(
    "@rules_cc//cc:action_names.bzl",
    _ACTION_NAMES = "ACTION_NAMES",
)

#
# NOTE: Reason for the below disabling of the 'docstring' is because this is called from the C/C++ toolchain rule implementation, thus it uses the same inputs
# and outputs as the rule implementation.
#
# buildifier: disable=function-docstring
def generate_base_actions(ctx):
    actions = []

    actions.append(
        _action_config(
            action_name = _ACTION_NAMES.assemble,
            tools = [
                _tool(path = "tools/assemble.sh"),
            ],
            implies = ["compiler_default_flags"],
        ),
    )

    actions.append(
        _action_config(
            action_name = _ACTION_NAMES.preprocess_assemble,
            tools = [
                _tool(path = "tools/preprocess_assemble.sh"),
            ],
            implies = ["compiler_default_flags"],
        ),
    )

    actions.append(
        _action_config(
            action_name = _ACTION_NAMES.c_compile,
            tools = [
                _tool(path = "tools/c_compile.sh"),
            ],
            implies = ["compiler_default_flags"],
        ),
    )

    actions.append(
        _action_config(
            action_name = _ACTION_NAMES.cpp_link_executable,
            enabled = True,
            tools = [
                _tool(path = "tools/cpp_link_executable.sh"),
            ],
            implies = [
                "shared_linker_parameters_file",
                "binary_linker_default_flags",
            ],
        ),
    )

    actions.append(
        _action_config(
            action_name = _ACTION_NAMES.cpp_link_dynamic_library,
            enabled = True,
            tools = [
                _tool(path = "tools/cpp_link_dynamic_library.sh"),
            ],
            implies = [
                "shared_linker_parameters_file",
                "binary_linker_default_flags",
            ],
        ),
    )

    actions.append(
        _action_config(
            action_name = _ACTION_NAMES.cpp_link_nodeps_dynamic_library,
            enabled = True,
            tools = [
                _tool(path = "tools/cpp_link_nodeps_dynamic_library.sh"),
            ],
            implies = [
                "shared_linker_parameters_file",
                "binary_linker_default_flags",
            ],
        ),
    )

    actions.append(
        _action_config(
            action_name = _ACTION_NAMES.cpp_link_static_library,
            enabled = True,
            tools = [
                _tool(path = "tools/cpp_link_static_library.sh"),
            ],
            implies = [
                "shared_linker_parameters_file",
                "static_library_linker_default_flags",
            ],
        ),
    )

    actions.append(
        _action_config(
            action_name = _ACTION_NAMES.strip,
            enabled = True,
            tools = [
                _tool(path = "tools/strip.sh"),
            ],
        ),
    )

    return actions
