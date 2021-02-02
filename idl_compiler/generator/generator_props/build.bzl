load("//idl_compiler:build_private.bzl", "IDLGeneratorPropertiesInfo")

def _idl_generator_props_impl(ctx):
    return [
        IDLGeneratorPropertiesInfo(
            handle_prefix = ctx.attr.handle_prefix,
            enumeration_prefix = ctx.attr.enumeration_prefix,
            enumeration_item_prefix = ctx.attr.enumeration_item_prefix,
            structure_prefix = ctx.attr.structure_prefix,
            function_prefix = ctx.attr.function_prefix,
        ),
    ]

idl_generator_props = rule(
    implementation = _idl_generator_props_impl,
    attrs = {
        "handle_prefix": attr.string(),
        "enumeration_prefix": attr.string(),
        "enumeration_item_prefix": attr.string(),
        "structure_prefix": attr.string(),
        "function_prefix": attr.string(),
    },
    provides = [IDLGeneratorPropertiesInfo],
)
