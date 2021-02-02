def model_configurations(manufacturer, architecture, model):
    native.config_setting(
        name = model,
        visibility = ["//visibility:public"],
        values = {
            "cpu": "arm",
        },
    )

def architecture_configurations(manufacturer, architecture):
    native.config_setting(
        name = architecture,
        visibility = ["//visibility:public"],
        values = {
            "cpu": "arm",
        },
    )

    native.constraint_value(
        name = "constraint",
        visibility = ["//visibility:public"],
        constraint_setting = "//randoms/foundation/build/platform/cpu:architecture",
    )

def manufacturer_configurations(manufacturer):
    native.config_setting(
        name = manufacturer,
        visibility = ["//visibility:public"],
        values = {
            "cpu": "arm",
        },
    )

    native.constraint_value(
        name = "constraint",
        visibility = ["//visibility:public"],
        constraint_setting = "//randoms/foundation/build/platform/cpu:manufacturer",
    )
