ThingConfigurationInfo = provider(
    fields = [
        "processor",
    ],
)

def _thing_configuration_impl(ctx):
    return [
        ThingConfigurationInfo(
            processor = ctx.build_setting_value,
        ),
    ]

thing_configuration = rule(
    implementation = _thing_configuration_impl,
    provides = [
        ThingConfigurationInfo,
    ],
    build_setting = config.string(flag = True),
)

ThingBaseInfo = provider(
    fields = [
        "processor",
        "blob",
    ],
)

def _thing_base_impl(ctx):
    configuration = ctx.attr._configuration[ThingConfigurationInfo]

    output_file = ctx.outputs.blob
    output_content = ""

    output_content += "%s" % configuration.processor

    ctx.actions.write(
        output = output_file,
        content = output_content,
        is_executable = False,
    )

    return [
        DefaultInfo(
            files = depset(
                [
                    output_file,
                ],
            ),
        ),
        ThingBaseInfo(
            processor = configuration.processor,
            blob = output_file,
        ),
    ]

_thing_base = rule(
    implementation = _thing_base_impl,
    attrs = {
        "_configuration": attr.label(
            default = "//machine_test:configuration",
            providers = [
                ThingConfigurationInfo,
            ],
        ),
    },
    outputs = {
        "blob": "%{name}.txt",
    },
    exec_groups = {
        "compile": exec_group(),
        "link": exec_group(),
    },
    provides = [
        DefaultInfo,
        ThingBaseInfo,
    ],
)

def _processor_transition_impl(settings, attrs):
    return [
        {
            "//machine_test:configuration": "APPLE",
        },
        {
            "//machine_test:configuration": "PEAR",
        },
        {
            "//machine_test:configuration": "YUZU",
        },
        {
            "//machine_test:configuration": "ORANGE",
        },
        {
            "//machine_test:configuration": "GRAPE",
        },
        {
            "//machine_test:configuration": "MANGO",
        },
        {
            "//machine_test:configuration": "GUAVA",
        },
        {
            "//machine_test:configuration": "LEMON",
        },
    ]

_processor_transition = transition(
    implementation = _processor_transition_impl,
    inputs = [],
    outputs = [
        "//machine_test:configuration",
    ],
)

def _thing_impl(ctx):
    files = []

    output_file = ctx.outputs.blob
    output_content = ""

    for binary_type in ctx.attr.binary:
        base_info = binary_type[ThingBaseInfo]
        processor = base_info.processor
        blob = base_info.blob

        files.append(blob)

        output_content += "%s=%s\n" % (
            processor,
            blob.path,
        )

    ctx.actions.write(
        output = output_file,
        content = output_content,
        is_executable = False,
    )

    runfiles = ctx.runfiles(
        files = [output_file],
        transitive_files = depset(files),
    )

    return [
        DefaultInfo(
            files = depset(
                [
                    output_file,
                ],
                transitive = [
                    depset(files),
                ],
            ),
            runfiles = runfiles,
        ),
    ]

_thing = rule(
    implementation = _thing_impl,
    attrs = {
        "binary": attr.label(
            cfg = _processor_transition,
        ),
        "_allowlist_function_transition": attr.label(
            default = "@bazel_tools//tools/allowlists/function_transition_allowlist",
        ),
    },
    outputs = {
        "blob": "%{name}.txt",
    },
    exec_groups = {
        "compile": exec_group(),
        "link": exec_group(),
    },
    provides = [
        DefaultInfo,
    ],
)

def thing(name, **kwargs):
    binary_name = "_%s_binary" % name

    _thing_base(
        name = binary_name,
        tags = ["manual"],
        **kwargs
    )

    _thing(
        name = name,
        binary = ":%s" % binary_name,
    )
