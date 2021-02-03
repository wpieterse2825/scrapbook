load("//old_projects/foundation/frameworks/core/types/x86/general:build.bzl", _BUILD_DESCRIPTOR_GENERAL = "BUILD_DESCRIPTOR")
load("//old_projects/foundation/frameworks/core/types/x86/mmx:build.bzl", _BUILD_DESCRIPTOR_MMX = "BUILD_DESCRIPTOR")
load("//old_projects/foundation/frameworks/core/types/x86/sse_1:build.bzl", _BUILD_DESCRIPTOR_SSE_1 = "BUILD_DESCRIPTOR")
load("//old_projects/foundation/frameworks/core/types/x86/sse_2:build.bzl", _BUILD_DESCRIPTOR_SSE_2 = "BUILD_DESCRIPTOR")
load("//old_projects/foundation/frameworks/core/types/x86/sse_3:build.bzl", _BUILD_DESCRIPTOR_SSE_3 = "BUILD_DESCRIPTOR")
load("//old_projects/foundation/frameworks/core/types/x86/ssse_3:build.bzl", _BUILD_DESCRIPTOR_SSSE_3 = "BUILD_DESCRIPTOR")
load("//old_projects/foundation/frameworks/core/types/x86/sse_4_1:build.bzl", _BUILD_DESCRIPTOR_SSE_4_1 = "BUILD_DESCRIPTOR")
load("//old_projects/foundation/frameworks/core/types/x86/sse_4_2:build.bzl", _BUILD_DESCRIPTOR_SSE_4_2 = "BUILD_DESCRIPTOR")
load("//old_projects/foundation/frameworks/core/types/x86/avx_1:build.bzl", _BUILD_DESCRIPTOR_AVX_1 = "BUILD_DESCRIPTOR")
load("//old_projects/foundation/frameworks/core/types/x86/avx_2:build.bzl", _BUILD_DESCRIPTOR_AVX_2 = "BUILD_DESCRIPTOR")
load("//old_projects/foundation/frameworks/core/types/x86/avx_512:build.bzl", _BUILD_DESCRIPTOR_AVX_512 = "BUILD_DESCRIPTOR")

BUILD_DESCRIPTOR = {
    "nice_name": "X86",
    "implementations": {
        "general": _BUILD_DESCRIPTOR_GENERAL,
        "mmx": _BUILD_DESCRIPTOR_MMX,
        "sse_1": _BUILD_DESCRIPTOR_SSE_1,
        "sse_2": _BUILD_DESCRIPTOR_SSE_2,
        "sse_3": _BUILD_DESCRIPTOR_SSE_3,
        "ssse_3": _BUILD_DESCRIPTOR_SSSE_3,
        "sse_4_1": _BUILD_DESCRIPTOR_SSE_4_1,
        "sse_4_2": _BUILD_DESCRIPTOR_SSE_4_2,
        "avx_1": _BUILD_DESCRIPTOR_AVX_1,
        "avx_2": _BUILD_DESCRIPTOR_AVX_2,
        "avx_512": _BUILD_DESCRIPTOR_AVX_512,
    },
}
