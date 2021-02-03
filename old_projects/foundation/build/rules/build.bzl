load(
    "//old_projects/foundation/frameworks:build.bzl",
    _FRAMEWORKS_BUILD_DESCRIPTOR = "BUILD_DESCRIPTOR",
)

BUILD_DESCRIPTOR = {
    "level_1": {
        "frameworks": _FRAMEWORKS_BUILD_DESCRIPTOR,
    },
}

def level_1_descriptor(level_1):
    level_1_db = BUILD_DESCRIPTOR["level_1"]

    return level_1_db[level_1]

def level_2_descriptor(
        level_1,
        level_2):
    level_1_descriptor_db = level_1_descriptor(level_1)
    level_2_db = level_1_descriptor_db["level_2"]

    return level_2_db[level_2]

def level_3_descriptor(
        level_1,
        level_2,
        level_3):
    level_2_descriptor_db = level_2_descriptor(level_1, level_2)
    level_3_db = level_2_descriptor_db["level_3"]

    return level_3_db[level_3]

def level_3_operations(
        level_1,
        level_2,
        level_3):
    level_3_descriptor_db = level_3_descriptor(level_1, level_2, level_3)

    return level_3_descriptor_db["operations"]

def level_3_operation_names(
        level_1,
        level_2,
        level_3):
    level_3_operations_db = level_3_operations(level_1, level_2, level_3)
    result = []

    for (operation_name, _) in level_3_operations_db.items():
        result.append(operation_name)

    return result

def level_3_operation_nice_name(
        level_1,
        level_2,
        level_3,
        level_3_operation):
    level_3_operations_db = level_3_operations(level_1, level_2, level_3)

    return level_3_operations_db[level_3_operation]

def level_3_platforms(
        level_1,
        level_2,
        level_3):
    level_3_descriptor_db = level_3_descriptor(level_1, level_2, level_3)

    return level_3_descriptor_db["platforms"]

def level_3_visibility(
        level_1,
        level_2,
        level_3):
    result = []

    result.append(
        "//old_projects/foundation/%s/%s/%s:__subpackages__" % (
            level_1,
            level_2,
            level_3,
        ),
    )

    return result

def level_3_platform_descriptor(
        level_1,
        level_2,
        level_3,
        level_3_platform):
    level_3_platforms_descriptor_db = level_3_platforms(level_1, level_2, level_3)

    return level_3_platforms_descriptor_db[level_3_platform]

def level_3_platform_nice_name(
        level_1,
        level_2,
        level_3,
        level_3_platform):
    level_3_platforms_descriptor_db = level_3_platform_descriptor(level_1, level_2, level_3, level_3_platform)

    return level_3_platforms_descriptor_db["nice_name"]

def level_3_implementations(
        level_1,
        level_2,
        level_3,
        level_3_platform):
    level_3_platforms_descriptor_db = level_3_platform_descriptor(level_1, level_2, level_3, level_3_platform)

    return level_3_platforms_descriptor_db["implementations"]

def level_3_implementation_descriptor(
        level_1,
        level_2,
        level_3,
        level_3_platform,
        level_3_implementation):
    level_3_implementations_db = level_3_implementations(level_1, level_2, level_3, level_3_platform)

    return level_3_implementations_db[level_3_implementation]

def level_3_implementation_nice_name(
        level_1,
        level_2,
        level_3,
        level_3_platform,
        level_3_implementation):
    level_3_implementations_descriptor_db = level_3_implementation_descriptor(level_1, level_2, level_3, level_3_platform, level_3_implementation)

    return level_3_implementations_descriptor_db["nice_name"]

def level_3_implementation_dependencies(
        level_1,
        level_2,
        level_3,
        level_3_platform,
        level_3_implementation):
    level_3_operations_db = level_3_operations(level_1, level_2, level_3)
    result = []

    for (operation_name, _) in level_3_operations_db.items():
        result.append(
            "//old_projects/foundation/%s/%s/%s/%s/%s:%s" % (
                level_1,
                level_2,
                level_3,
                level_3_platform,
                level_3_implementation,
                operation_name,
            ),
        )

    return result
