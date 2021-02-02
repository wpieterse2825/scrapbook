#include <immintrin.h>

#include <fstream>
#include <iostream>

#include "tools/cpp/runfiles/runfiles.h"

#include "doom_3_map/map.pb.h"

using bazel::tools::cpp::runfiles::Runfiles;

int main(int argc, char** argv) {
    std::string               runfiles_error {""};
    std::unique_ptr<Runfiles> runfiles {Runfiles::Create(argv[0], &runfiles_error)};

    GOOGLE_PROTOBUF_VERIFY_VERSION;

    if (runfiles == nullptr) {
        std::cout << "ERROR: Failed to initialize run-files : " << runfiles_error << std::endl;
    }

    std::string  map_path = runfiles->Rlocation("scrapbook/doom_3_map/delta4.pb");
    std::fstream map_file {map_path, std::ios::in | std::ios::binary};
    Map          map_object;

    map_object.ParseFromIstream(&map_file);

    uint64_t entities = 0;
    uint64_t brushes  = 0;
    uint64_t sides    = 0;
    uint64_t patches  = 0;
    for (const auto& entity : map_object.entities()) {
        entities++;

        for (const auto& primitive : entity.primitives()) {
            auto primitive_type = primitive.primitive_type_case();

            if (primitive_type == Primitive::kBrush) {
                auto brush = primitive.brush();

                brushes++;
                for (const auto& side : brush.sides()) {
                    auto comparend_plane = side.plane();
                    sides++;
                }
            } else if (primitive_type == Primitive::kPatch) {
                patches++;
            }
        }
    }

    std::cout << "entities : " << entities << std::endl;
    std::cout << "brushes  : " << brushes << std::endl;
    std::cout << "sides    : " << sides << std::endl;
    std::cout << "patches  : " << patches << std::endl;

    google::protobuf::ShutdownProtobufLibrary();
    return 0;
}
