IDLGeneratorPropertiesInfo = provider(
    fields = [
        "handle_prefix",
        "enumeration_prefix",
        "enumeration_item_prefix",
        "structure_prefix",
        "function_prefix",
    ],
)

IDLCompilerToolchainInfo = provider(
    fields = [
        "handle_compiler",
        "enumeration_compiler",
        "structure_compiler",
        "function_compiler",
    ],
)

IDLLinkerToolchainInfo = provider(
    fields = [
        "archive",
    ],
)

IDLGeneratorToolchainInfo = provider(
    fields = [
        "generator_c",
        "generator_cpp",
    ],
)

IDLHandleInfo = provider(
    fields = [
        "binary",
    ],
)

IDLEnumerationInfo = provider(
    fields = [
        "binary",
    ],
)

IDLStructureInfo = provider(
    fields = [
        "binary",
    ],
)

IDLFunctionInfo = provider(
    fields = [
        "binary",
    ],
)

IDLArchiveInfo = provider(
    fields = [
        "binary",
    ],
)

IDLGeneratorInfo = provider(
    fields = [
        "generated",
    ],
)
