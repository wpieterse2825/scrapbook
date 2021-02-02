def _worker_copy_impl(ctx):
    tool = ctx.executable._tool

    source = ctx.file.input
    destination = ctx.actions.declare_file(ctx.label.name)

    arguments_file = ctx.actions.declare_file(ctx.label.name + "_arguments")
    arguments_content = ""

    arguments_content += "--source\n%s\n" % source.path
    arguments_content += "--destination\n%s\n" % destination.path

    ctx.actions.write(
        output = arguments_file,
        content = arguments_content,
    )

    ctx.actions.run(
        inputs = [
            source,
            arguments_file,
        ],
        outputs = [
            destination,
        ],
        arguments = [
            "@%s" % arguments_file.path,
        ],
        executable = tool,
        tools = [
            tool,
        ],
        execution_requirements = {
            "supports-workers": "1",
        },
    )

    return [
        DefaultInfo(
            files = depset(
                [
                    destination,
                ],
            ),
        ),
    ]

worker_copy = rule(
    implementation = _worker_copy_impl,
    attrs = {
        "input": attr.label(
            mandatory = True,
            allow_single_file = [
                ".txt",
            ],
        ),
        "_tool": attr.label(
            executable = True,
            cfg = "host",
            default = "//persistent_worker/tool",
        ),
    },
)
