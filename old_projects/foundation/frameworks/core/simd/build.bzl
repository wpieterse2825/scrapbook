load("//old_projects/foundation/frameworks/core/simd/common:build.bzl", _BUILD_DESCRIPTOR_COMMON = "BUILD_DESCRIPTOR")
load("//old_projects/foundation/frameworks/core/simd/x86:build.bzl", _BUILD_DESCRIPTOR_X86 = "BUILD_DESCRIPTOR")

BUILD_DESCRIPTOR = {
    "operations": {
        "arithmetic": "Arithmetic",
        "bit_manipulation": "BitManipulation",
        "cast": "Cast",
        "compare": "Compare",
        "convert": "Convert",
        "cryptography": "Cryptography",
        "load": "Load",
        "logical": "Logical",
        "mask": "Mask",
        "math": "Math",
        "miscellaneous": "Miscellaneous",
        "move": "Move",
        "random": "Random",
        "set": "Set",
        "statistics": "Statistics",
        "store": "Store",
        "string": "String",
        "swizzle": "Swizzle",
        "trigonometry": "Trigonometry",
    },
    "platforms": {
        "common": _BUILD_DESCRIPTOR_COMMON,
        "x86": _BUILD_DESCRIPTOR_X86,
    },
}
