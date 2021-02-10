load(
    "@rules_cc//cc:defs.bzl",
    "cc_library",
)

cc_library(
    name = "celero",
    srcs = glob(
        [
            "src/*.cpp",
        ],
    ),
    hdrs = glob(
        [
            "include/celero/*.h",
        ],
    ),
    strip_include_prefix = "include",
    visibility = [
        "//visibility:public",
    ],
)
