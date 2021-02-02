def _multiplex_worker_thing_impl(ctx):
    tool = ctx.executable._tool

    src = ctx.file.input
    dst = ctx.actions.declare_file(ctx.label.name)

    args_file = ctx.actions.declare_file(ctx.label.name + "_arguments")
    args_content = ""

    args_content += "--source\n%s\n" % src.path
    args_content += "--destination\n%s\n" % dst.path

    ctx.actions.write(
        output = args_file,
        content = args_content,
    )

    ctx.actions.run(
        inputs = [
            src,
            args_file,
        ],
        outputs = [
            dst,
        ],
        arguments = [
            "@%s" % args_file.path,
        ],
        executable = tool,
        tools = [
            tool,
        ],
        execution_requirements = {
            "supports-workers": "1",
            "requires-worker-protocol": "json",
        },
    )

    return [
        DefaultInfo(
            files = depset(
                [
                    dst,
                ],
            ),
        ),
    ]

multiplex_worker_thing = rule(
    implementation = _multiplex_worker_thing_impl,
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
            default = "//multiplex_worker/tool",
        ),
    },
)
