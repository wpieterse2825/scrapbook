load("//old_projects/foundation/frameworks/core/types/common:build.bzl", _BUILD_DESCRIPTOR_COMMON = "BUILD_DESCRIPTOR")
load("//old_projects/foundation/frameworks/core/types/x86:build.bzl", _BUILD_DESCRIPTOR_X86 = "BUILD_DESCRIPTOR")

BUILD_DESCRIPTOR = {
    "operations": {
        "auxiliary": "Auxiliary",
        "character": "Character",
        "decimal": "Decimal",
        "integer": "Integer",
        "pack": "Pack",
        "pointer": "Pointer",
    },
    "platforms": {
        "common": _BUILD_DESCRIPTOR_COMMON,
        "x86": _BUILD_DESCRIPTOR_X86,
    },
}
