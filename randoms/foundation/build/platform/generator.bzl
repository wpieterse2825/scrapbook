load("//build/platform/cpu:database.bzl", _cpu_database = "database")

def _generate_cpu_platform_constraints(model):
    base_path = "//build/platform/cpu"

    manufacturer_path = "%s/%s" % (
        base_path,
        model.manufacturer,
    )

    architecture_path = "%s/%s" % (
        manufacturer_path,
        model.architecture,
    )

    model_path = "%s/%s" % (
        architecture_path,
        model.model,
    )

    return [
        "%s:constraint" % manufacturer_path,
        "%s:constraint" % architecture_path,
        "%s:constraint" % model_path,
    ]


def _generate_platform(cpu_model):
    final_constraints = []

    cpu_name = cpu_model.name

    final_constraints += _generate_cpu_platform_constraints(cpu_model)

    native.platform(
        name = "%s" % cpu_model.name,
        constraint_values = final_constraints
    )

def platform_configurations():
    for manufacturer_name in _cpu_database.supported_manufacturers():
        manufacturer_db = _cpu_database.manufacturer(manufacturer_name)

        for architecture_name in manufacturer_db.supported_architectures(manufacturer_db):
            architecture_db = manufacturer_db.architecture(manufacturer_db, architecture_name)

            for model_name in architecture_db.supported_models(architecture_db):
                model_db = architecture_db.model(architecture_db, model_name)
                operating_modes = model_db.operating_modes(model_db)

                for operating_mode_name in operating_modes:
                    model_details = struct(
                        name = "%s_%s_%s_%s" % (
                            manufacturer_name,
                            architecture_name,
                            model_name,
                            operating_mode,
                        ),
                        manufacturer = manufacturer_name,
                        architecture = architecture_name,
                        model = model_name,
                        operating_mode = operating_mode_name,
                    )

                    _generate_platform(model_details)
