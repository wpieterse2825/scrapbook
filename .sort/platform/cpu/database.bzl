load("//randoms/foundation/build/platform/cpu:datasheet.bzl", _MANUFACTURERS = "MANUFACTURERS")

def _model_operating_modes(db):
    results = []
    model = db.details
    socket_layout = model["socket_layout"]
    socket_cores = socket_layout["cores"]

    for core_id in range(socket_cores):
        core_name = "core_%s" % core_id

        core_layout = socket_layout[core_name]
        core_threads = core_layout["threads"]

        for thread_id in range(core_threads):
            thread_name = "thread_%s" % thread_id

            thread_layout = core_layout[thread_name]
            thread_operating_modes = thread_layout["operating_modes"]

            found = False
            for (mode_name, _) in thread_operating_modes.items():
                for result_mode_name in results:
                    if result_mode_name == mode_name:
                        found = True

                if found == False:
                    results.append(mode_name)

    return results

def _model_name(db):
    return db.details["model"]

def _supported_models(db):
    results = []

    for (model_name, _) in db.details.items():
        results.append(model_name)

    return results

def _model(db, model_name):
    model_details = db.details[model_name]

    return struct(
        details = model_details,
        name = _model_name,
        operating_modes = _model_operating_modes,
    )

def _supported_architectures(db):
    results = []

    for (architecture_name, _) in db.details.items():
        results.append(architecture_name)

    return results

def _architecture(db, architecture_name):
    architecture_details = db.details[architecture_name]

    return struct(
        details = architecture_details,
        supported_models = _supported_models,
        model = _model,
    )

def _supported_manufacturers():
    results = []

    for (manufacturer_name, _) in _MANUFACTURERS.items():
        results.append(manufacturer_name)

    return results

def _manufacturer(manufacturer_name):
    manufacturer_details = _MANUFACTURERS[manufacturer_name]

    return struct(
        details = manufacturer_details,
        supported_architectures = _supported_architectures,
        architecture = _architecture,
    )

database = struct(
    supported_manufacturers = _supported_manufacturers,
    manufacturer = _manufacturer,
)
