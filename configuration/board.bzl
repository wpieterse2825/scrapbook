load("@bazel_skylib//rules:common_settings.bzl", "BuildSettingInfo")

BoardThingInfo = provider(
    fields = [
        "file",
    ],
)

def _board_thing_impl(ctx):
    output_file = ctx.actions.declare_file("%s.txt" % ctx.label.name)
    output_content = ""

    output_content = "%s\n" % ctx.attr._board_name[BuildSettingInfo].value

    ctx.actions.write(
        output = output_file,
        content = output_content,
    )

    return [
        BoardThingInfo(
            file = output_file,
        ),
    ]

board_thing = rule(
    implementation = _board_thing_impl,
    attrs = {
        "_board_name": attr.label(
            default = Label("//configuration:board_name"),
        ),
    },
)

def _board_transition_impl(settings, attrs):
    return {
        "//configuration:board_name": "chromebook",
    }

_board_transition = transition(
    implementation = _board_transition_impl,
    inputs = [],
    outputs = [
        "//configuration:board_name",
    ],
)

ConfigurationInfo = provider(
    fields = [
        "board_name",
    ],
)

def _board_configuration_impl(ctx):
    return [
        ConfigurationInfo(
            board_name = ctx.attr._board_name[BuildSettingInfo].value,
        ),
    ]

board_configuration = rule(
    implementation = _board_configuration_impl,
    attrs = {
        "_board_name": attr.label(
            default = Label("//configuration:board_name"),
        ),
    },
)

def _board_impl(ctx):
    thing_file = ctx.attr.thing[BoardThingInfo].file

    output_file = ctx.actions.declare_file("%s_me.txt" % ctx.label.name)
    output_content = ""

    output_content = "%s\n" % ctx.attr.config[ConfigurationInfo].board_name

    ctx.actions.write(
        output = output_file,
        content = output_content,
    )

    return [
        DefaultInfo(
            files = depset(
                [
                    thing_file,
                    output_file,
                ],
            ),
        ),
    ]

board = rule(
    implementation = _board_impl,
    cfg = _board_transition,
    attrs = {
        "thing": attr.label(
            mandatory = True,
        ),
        "config": attr.label(
            mandatory = True,
            providers = [
                ConfigurationInfo,
            ],
        ),
        "_whitelist_function_transition": attr.label(
            default = "@bazel_tools//tools/whitelists/function_transition_whitelist",
        ),
    },
)
