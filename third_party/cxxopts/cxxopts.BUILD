load(
    "@rules_cc//cc:defs.bzl",
    "cc_library",
)

cc_library(
    name = "cxxopts",
    hdrs = glob(
        [
            "include/*.hpp",
        ],
    ),
    strip_include_prefix = "include",
    visibility = [
        "//visibility:public",
    ],
)
