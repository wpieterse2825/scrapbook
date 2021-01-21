#
# Copyright 2020 - The World Tree and the The World Tree contributors.
# SPDX-License-Identifier: MIT
#

"""Base C/C++ toolchain features common to all processors."""

load(
    "@rules_cc//cc:cc_toolchain_config_lib.bzl",
    _feature = "feature",
    _flag_group = "flag_group",
    _flag_set = "flag_set",
    _variable_with_value = "variable_with_value",
)
load(
    "@rules_cc//cc:action_names.bzl",
    _ACTION_NAMES = "ACTION_NAMES",
)

#
# Features:
#  - static_linking_mode
#  - dynamic_linking_mode - Enabled by default for linking mode.
#  - per_object_debug_info - Enabled with fission, e.g: --fission.
#  - supports_interface_shared_libraries - Uses --interface_shared_objects, optimization.
#  - static_link_cpp_runtimes - How to link in the run-time library. Dynamic with dynamic libraries, static with static libraries.
#  - supports_pic - If enabled, will use PIC for shared libraries. 'pic' is present when PIC is needed. Can be overriden with --force_pic.
#

#
# NOTE: Reason for the below disabling of the 'docstring' is because this is called from the C/C++ toolchain rule implementation, thus it uses the same inputs
# and outputs as the rule implementation.
#
# buildifier: disable=function-docstring
def generate_base_features(ctx):
    features = []

    features.append(
        _feature(
            name = "no_legacy_features",
            enabled = True,
        ),
    )

    features.append(
        _feature(
            name = "supports_start_end_lib",
            enabled = True,
        ),
    )

    features.append(
        _feature(
            name = "supports_dynamic_linker",
            enabled = True,
        ),
    )

    features.append(
        _feature(
            name = "opt",
            implies = ["common"],
        ),
    )

    features.append(
        _feature(
            name = "dbg",
            implies = ["common"],
        ),
    )

    features.append(
        _feature(
            name = "fastbuild",
            implies = ["common"],
        ),
    )

    features.append(
        _feature(
            name = "common",
            implies = [
                "processor_{processor}_{bit_width}_{endianess}".format(
                    processor = ctx.attr.processor,
                    bit_width = ctx.attr.bit_width,
                    endianess = ctx.attr.endianess,
                ),
            ] + ctx.attr.extra_features,
        ),
    )

    features.append(
        _feature(
            name = "freestanding",
            flag_sets = [
                _flag_set(
                    actions = [
                        _ACTION_NAMES.assemble,
                        _ACTION_NAMES.preprocess_assemble,
                        _ACTION_NAMES.c_compile,
                        _ACTION_NAMES.cpp_link_executable,
                        _ACTION_NAMES.cpp_link_dynamic_library,
                        _ACTION_NAMES.cpp_link_nodeps_dynamic_library,
                    ],
                    flag_groups = [
                        _flag_group(
                            flags = ["-ffreestanding"],
                        ),
                    ],
                ),
            ],
            implies = [
                "no_builtins",
                "no_standard_includes",
                "no_standard_library",
            ],
        ),
    )

    features.append(
        _feature(
            name = "no_builtins",
            flag_sets = [
                _flag_set(
                    actions = [
                        _ACTION_NAMES.assemble,
                        _ACTION_NAMES.preprocess_assemble,
                        _ACTION_NAMES.c_compile,
                    ],
                    flag_groups = [
                        _flag_group(
                            flags = ["-fno-builtin"],
                        ),
                    ],
                ),
            ],
        ),
    )

    features.append(
        _feature(
            name = "no_standard_includes",
            flag_sets = [
                _flag_set(
                    actions = [
                        _ACTION_NAMES.assemble,
                        _ACTION_NAMES.preprocess_assemble,
                        _ACTION_NAMES.c_compile,
                    ],
                    flag_groups = [
                        _flag_group(
                            flags = ["-nostdinc"],
                        ),
                    ],
                ),
            ],
        ),
    )

    features.append(
        _feature(
            name = "no_standard_library",
            flag_sets = [
                _flag_set(
                    actions = [
                        _ACTION_NAMES.cpp_link_executable,
                        _ACTION_NAMES.cpp_link_dynamic_library,
                        _ACTION_NAMES.cpp_link_nodeps_dynamic_library,
                    ],
                    flag_groups = [
                        _flag_group(
                            flags = ["-nostdlib"],
                        ),
                    ],
                ),
            ],
        ),
    )

    features.append(
        _feature(
            name = "compiler_default_flags",
            flag_sets = [
                _flag_set(
                    actions = [
                        _ACTION_NAMES.assemble,
                        _ACTION_NAMES.preprocess_assemble,
                        _ACTION_NAMES.c_compile,
                    ],
                    flag_groups = [
                        _flag_group(
                            flags = [
                                "-c",
                                "%{source_file}",
                            ],
                            expand_if_available = "source_file",
                        ),
                        _flag_group(
                            flags = [
                                "-o",
                                "%{output_file}",
                            ],
                            expand_if_available = "output_file",
                        ),
                        _flag_group(
                            flags = [
                                "-MD",
                                "-MF",
                                "%{dependency_file}",
                            ],
                            expand_if_available = "dependency_file",
                        ),
                        _flag_group(
                            flags = [
                                "-include",
                                "%{includes}",
                            ],
                            iterate_over = "includes",
                            expand_if_available = "includes",
                        ),
                        _flag_group(
                            flags = ["-I%{include_paths}"],
                            iterate_over = "include_paths",
                        ),
                        _flag_group(
                            flags = [
                                "-iquote",
                                "%{quote_include_paths}",
                            ],
                            iterate_over = "quote_include_paths",
                        ),
                        _flag_group(
                            flags = [
                                "-isystem",
                                "%{system_include_paths}",
                            ],
                            iterate_over = "system_include_paths",
                        ),
                    ],
                ),
            ],
        ),
    )

    features.append(
        _feature(
            name = "shared_linker_parameters_file",
            flag_sets = [
                _flag_set(
                    actions = [
                        _ACTION_NAMES.cpp_link_executable,
                        _ACTION_NAMES.cpp_link_dynamic_library,
                        _ACTION_NAMES.cpp_link_nodeps_dynamic_library,
                        _ACTION_NAMES.cpp_link_static_library,
                    ],
                    flag_groups = [
                        _flag_group(
                            flags = ["@%{linker_param_file}"],
                            expand_if_available = "linker_param_file",
                        ),
                    ],
                ),
            ],
        ),
    )

    features.append(
        _feature(
            name = "binary_linker_default_flags",
            flag_sets = [
                _flag_set(
                    actions = [
                        _ACTION_NAMES.cpp_link_executable,
                        _ACTION_NAMES.cpp_link_dynamic_library,
                        _ACTION_NAMES.cpp_link_nodeps_dynamic_library,
                    ],
                    flag_groups = [
                        _flag_group(
                            iterate_over = "libraries_to_link",
                            flag_groups = [
                                _flag_group(
                                    flags = ["-Wl,--start-lib"],
                                    expand_if_equal = _variable_with_value(
                                        name = "libraries_to_link.type",
                                        value = "object_file_group",
                                    ),
                                ),
                                _flag_group(
                                    flags = ["-whole-archive"],
                                    expand_if_true = "libraries_to_link.is_whole_archive",
                                ),
                                _flag_group(
                                    flags = ["%{libraries_to_link.object_files}"],
                                    iterate_over = "libraries_to_link.object_files",
                                    expand_if_equal = _variable_with_value(
                                        name = "libraries_to_link.type",
                                        value = "object_file_group",
                                    ),
                                ),
                                _flag_group(
                                    flags = ["%{libraries_to_link.name}"],
                                    expand_if_equal = _variable_with_value(
                                        name = "libraries_to_link.type",
                                        value = "object_file",
                                    ),
                                ),
                                _flag_group(
                                    flags = ["%{libraries_to_link.name}"],
                                    expand_if_equal = _variable_with_value(
                                        name = "libraries_to_link.type",
                                        value = "interface_library",
                                    ),
                                ),
                                _flag_group(
                                    flags = ["%{libraries_to_link.name}"],
                                    expand_if_equal = _variable_with_value(
                                        name = "libraries_to_link.type",
                                        value = "static_library",
                                    ),
                                ),
                                _flag_group(
                                    flags = ["-l%{libraries_to_link.name}"],
                                    expand_if_equal = _variable_with_value(
                                        name = "libraries_to_link.type",
                                        value = "dynamic_library",
                                    ),
                                ),
                                _flag_group(
                                    flags = ["-l:%{libraries_to_link.name}"],
                                    expand_if_equal = _variable_with_value(
                                        name = "libraries_to_link.type",
                                        value = "versioned_dynamic_library",
                                    ),
                                ),
                                _flag_group(
                                    flags = ["-no-whole-archive"],
                                    expand_if_true = "libraries_to_link.is_whole_archive",
                                ),
                                _flag_group(
                                    flags = ["-Wl,--end-lib"],
                                    expand_if_equal = _variable_with_value(
                                        name = "libraries_to_link.type",
                                        value = "object_file_group",
                                    ),
                                ),
                            ],
                            expand_if_available = "libraries_to_link",
                        ),
                        _flag_group(
                            flags = [
                                "-o",
                                "%{output_execpath}",
                            ],
                            expand_if_available = "output_execpath",
                        ),
                    ],
                ),
            ],
        ),
    )

    features.append(
        _feature(
            name = "static_library_linker_default_flags",
            flag_sets = [
                _flag_set(
                    actions = [
                        _ACTION_NAMES.cpp_link_static_library,
                    ],
                    flag_groups = [
                        _flag_group(
                            flags = ["rcsD"],
                        ),
                        _flag_group(
                            iterate_over = "libraries_to_link",
                            flag_groups = [
                                _flag_group(
                                    flags = ["%{libraries_to_link.name}"],
                                    expand_if_equal = _variable_with_value(
                                        name = "libraries_to_link.type",
                                        value = "object_file",
                                    ),
                                ),
                                _flag_group(
                                    flags = ["%{libraries_to_link.object_files}"],
                                    iterate_over = "libraries_to_link.object_files",
                                    expand_if_equal = _variable_with_value(
                                        name = "libraries_to_link.type",
                                        value = "object_file_group",
                                    ),
                                ),
                            ],
                            expand_if_available = "libraries_to_link",
                        ),
                        _flag_group(
                            flags = ["%{output_execpath}"],
                            expand_if_available = "output_execpath",
                        ),
                    ],
                ),
            ],
        ),
    )

    return features
