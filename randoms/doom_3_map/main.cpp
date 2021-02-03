#include <fstream>
#include <iostream>

#include "tools/cpp/runfiles/runfiles.h"

#include "randoms/doom_3_map/map.pb.h"

using bazel::tools::cpp::runfiles::Runfiles;

int main(int argument_count, char** arguments) {
    std::string map_name{"delta4"};
    std::string               runfiles_error {""};
    std::unique_ptr<Runfiles> runfiles {Runfiles::Create(arguments[0], &runfiles_error)};

    GOOGLE_PROTOBUF_VERIFY_VERSION;

    std::cout << "Doom 3 map processor (" << map_name << ".pb):" << std::endl;

    if (runfiles == nullptr) {
        std::cout << "ERROR: Failed to initialize run-files : " << runfiles_error << std::endl;
        return 1;
    }

    std::string  map_path = runfiles->Rlocation("scrapbook/randoms/doom_3_map/maps/" + map_name + ".pb");
    std::fstream map_file {map_path, std::ios::in | std::ios::binary};
    if (!map_file) {
        std::cout << "ERROR: Failed to open map-file : " << map_path << std::endl;
        return 1;
    }

    Map map_object;
    if (!map_object.ParseFromIstream(&map_file)) {
        std::cout << "ERROR: Failed to parse map file" << std::endl;
        return 1;
    }

    uint64_t entities = 0;
    uint64_t primitives = 0;
    uint64_t brushes  = 0;
    uint64_t sides    = 0;
    uint64_t patches  = 0;
    for (const auto& entity : map_object.entities()) {
        entities++;

        for (const auto& primitive : entity.primitives()) {
            auto primitive_type = primitive.primitive_type_case();

            primitives++;
            if (primitive_type == Primitive::kBrush) {
                auto brush = primitive.brush();

                brushes++;
                for (const auto& side : brush.sides()) {
                    sides++;
                }
            } else if (primitive_type == Primitive::kPatch) {
                patches++;
            }
        }
    }

    std::cout << " - Entities   : " << entities << std::endl;
    std::cout << " - Primitives : " << primitives << std::endl;
    std::cout << " - Brushes    : " << brushes << std::endl;
    std::cout << " - Sides      : " << sides << std::endl;
    std::cout << " - Patches    : " << patches << std::endl;

    google::protobuf::ShutdownProtobufLibrary();
    return 0;
}
