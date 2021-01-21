load("//frameworks/core/concepts:build.bzl", _BUILD_DESCRIPTOR_CONCEPTS = "BUILD_DESCRIPTOR")
load("//frameworks/core/simd:build.bzl", _BUILD_DESCRIPTOR_SIMD = "BUILD_DESCRIPTOR")
load("//frameworks/core/traits:build.bzl", _BUILD_DESCRIPTOR_TRAITS = "BUILD_DESCRIPTOR")
load("//frameworks/core/types:build.bzl", _BUILD_DESCRIPTOR_TYPES = "BUILD_DESCRIPTOR")

BUILD_DESCRIPTOR = {
    "level_3": {
        "concepts": _BUILD_DESCRIPTOR_CONCEPTS,
        "simd": _BUILD_DESCRIPTOR_SIMD,
        "traits": _BUILD_DESCRIPTOR_TRAITS,
        "types": _BUILD_DESCRIPTOR_TYPES,
    },
}
