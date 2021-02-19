#include <fstream>
#include <iostream>

#include "tools/cpp/runfiles/runfiles.h"

#include "randoms/doom_3_map/map.pb.h"

#include "randoms/doom_3_map/map.h"

using bazel::tools::cpp::runfiles::Runfiles;

char* StringCopy(const char* input) {
    size_t input_length = strlen(input);
    char*  output       = (char*)malloc(input_length + 1);

    strncpy(output, input, input_length);
    output[input_length] = '\0';

    return output;
}

int main(int argument_count, char** arguments) {
    std::string               map_name {"delta4"};
    std::string               runfiles_error {""};
    std::unique_ptr<Runfiles> runfiles {Runfiles::Create(arguments[0], &runfiles_error)};

    GOOGLE_PROTOBUF_VERIFY_VERSION;

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

    uint64_t entities                 = 0;
    uint64_t entity_configurations    = 0;
    uint64_t primitives               = 0;
    uint64_t primitives_brushes       = 0;
    uint64_t primitives_brushes_sides = 0;
    uint64_t primitives_patches       = 0;
    for (const auto& entity : map_object.entities()) {
        entities++;

        for (const auto& configuration : entity.configuration()) {
            (void)configuration;

            entity_configurations++;
        }

        for (const auto& primitive : entity.primitives()) {
            auto primitive_type = primitive.primitive_type_case();

            primitives++;
            if (primitive_type == Primitive::kBrush) {
                auto brush = primitive.brush();

                primitives_brushes++;

                for (const auto& side : brush.sides()) {
                    (void)side;

                    primitives_brushes_sides++;
                }
            } else if (primitive_type == Primitive::kPatch) {
                primitives_patches++;
            }
        }
    }

    /*
    std::cout << "Entities       : " << entities << std::endl;
    std::cout << "Configurations : " << entity_configurations << std::endl;
    std::cout << "Primitives     : " << primitives << std::endl;
    std::cout << "Brushes        : " << primitives_brushes << std::endl;
    std::cout << "Sides          : " << primitives_brushes_sides << std::endl;
    std::cout << "Patches        : " << primitives_patches << std::endl;
    std::cout << std::endl;
    */

    map_t map_normal;

    map_normal.name         = StringCopy(map_object.name().c_str());
    map_normal.entity_count = entities;
    map_normal.entities     = (entity_t*)malloc(entities * sizeof(entity_t));

    entities = 0;
    for (const auto& entity : map_object.entities()) {
        entity_t* current_entity = &map_normal.entities[entities];
        entities++;

        entity_configurations    = 0;
        primitives               = 0;
        primitives_brushes       = 0;
        primitives_patches       = 0;
        primitives_brushes_sides = 0;

        for (const auto& configuration : entity.configuration()) {
            (void)configuration;

            entity_configurations++;
        }

        for (const auto& primitive : entity.primitives()) {
            auto primitive_type = primitive.primitive_type_case();

            primitives++;
            if (primitive_type == Primitive::kBrush) {
                primitives_brushes++;
            } else if (primitive_type == Primitive::kPatch) {
                primitives_patches++;
            }
        }

        current_entity->configuration_count     = entity_configurations;
        current_entity->primitive_brushes_count = primitives_brushes;
        current_entity->primitive_patches_count = primitives_patches;

        current_entity->configuration     = (entity_key_value_t*)malloc(entity_configurations * sizeof(entity_key_value_t));
        current_entity->primitive_brushes = (primitive_brush_t*)malloc(primitives_brushes * sizeof(primitive_brush_t));
        current_entity->primitive_patches = (primitive_patch_t*)malloc(primitives_patches * sizeof(primitive_patch_t));

        entity_configurations = 0;
        for (const auto& configuration : entity.configuration()) {
            entity_key_value_t* current_configuration = &current_entity->configuration[entity_configurations];
            entity_configurations++;

            current_configuration->key   = StringCopy(configuration.first.c_str());
            current_configuration->value = StringCopy(configuration.second.c_str());
        }

        primitives_brushes = 0;
        primitives_patches = 0;
        for (const auto& primitive : entity.primitives()) {
            auto primitive_type = primitive.primitive_type_case();

            if (primitive_type == Primitive::kBrush) {
                auto brush = primitive.brush();

                primitive_brush_t* current_brush = &current_entity->primitive_brushes[primitives_brushes];
                primitives_brushes++;

                uint64_t primitives_brushes_sides = 0;
                for (const auto& side : brush.sides()) {
                    (void)side;

                    primitives_brushes_sides++;
                }

                current_brush->sides_count = primitives_brushes_sides;
                current_brush->sides       = (primitive_brush_side_t*)malloc(primitives_brushes_sides * sizeof(primitive_brush_side_t));

                primitives_brushes_sides = 0;
                for (const auto& side : brush.sides()) {
                    primitive_brush_side_t* current_side = &current_brush->sides[primitives_brushes_sides];
                    primitives_brushes_sides++;

                    current_side->material                  = StringCopy(side.material().c_str());
                    current_side->plane.normal_x            = side.plane().normal_x();
                    current_side->plane.normal_y            = side.plane().normal_y();
                    current_side->plane.normal_z            = side.plane().normal_z();
                    current_side->plane.distance            = side.plane().distance();
                    current_side->texture_matrix.u_offset_x = side.texture_matrix().u_offset_x();
                    current_side->texture_matrix.u_offset_y = side.texture_matrix().u_offset_y();
                    current_side->texture_matrix.u_offset_z = side.texture_matrix().u_offset_z();
                    current_side->texture_matrix.v_offset_x = side.texture_matrix().v_offset_x();
                    current_side->texture_matrix.v_offset_y = side.texture_matrix().v_offset_y();
                    current_side->texture_matrix.v_offset_z = side.texture_matrix().v_offset_z();
                }
            } else if (primitive_type == Primitive::kPatch) {
                auto patch = primitive.patch();

                primitive_patch_t* current_patch = &current_entity->primitive_patches[primitives_patches];
                primitives_patches++;

                current_patch->material               = StringCopy(patch.material().c_str());
                current_patch->explicitly_subdivided  = patch.explicitly_subdivided();
                current_patch->subdivision_horizontal = patch.subdivisions_horizontal();
                current_patch->subdivision_vertical   = patch.subdivisions_vertical();
            }
        }
    }

    ProcessMap(&map_normal);

    google::protobuf::ShutdownProtobufLibrary();
    return 0;
}
