load("//randoms/foundation/build/rules/header:platform_export_header_source.bzl", _platform_export_header_source = "platform_export_header_source")

def platform_export_header(
        name,
        level_1,
        level_2,
        level_3,
        level_3_platform):
    generated_name = "_platform_export_header_generated_%s" % level_3_platform
    copy_name = "_platform_export_header_copy_%s" % level_3_platform
    header_name = "%s.hpp" % level_3_platform

    _platform_export_header_source(
        name = generated_name,
        level_1 = level_1,
        level_2 = level_2,
        level_3 = level_3,
        level_3_platform = level_3_platform,
    )

    native.genrule(
        name = copy_name,
        srcs = [":%s" % generated_name],
        outs = [header_name],
        cmd = "cp $(SRCS) $@",
    )
