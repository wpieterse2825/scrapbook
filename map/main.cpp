#include <immintrin.h>

#include <cmath>
#include <fstream>
#include <iostream>

#include "tools/cpp/runfiles/runfiles.h"

#include "map/map.pb.h"

using bazel::tools::cpp::runfiles::Runfiles;

struct FPlane {
    float x;
    float y;
    float z;
    float distance;
};

struct FPlaneSIMDSet {
    float x[8];
    float y[8];
    float z[8];
    float distance[8];
};

FPlane  global_planes[8 * 1024] = {};
int64_t global_planes_count     = 0;

FPlane  compressed_planes[8 * 1024] = {};
int64_t compressed_planes_count     = 0;

#define NORMAL_EPSILON   0.00001f
#define DISTANCE_EPSILON 0.01f

bool Compare(FPlane lhs, FPlane rhs, float normal_epsilon, float distance_epsilon) {
    auto lhs_x        = lhs.x;
    auto lhs_y        = lhs.y;
    auto lhs_z        = lhs.z;
    auto lhs_distance = lhs.distance;

    auto rhs_x        = rhs.x;
    auto rhs_y        = rhs.y;
    auto rhs_z        = rhs.z;
    auto rhs_distance = rhs.distance;

    auto x_value = lhs_x - rhs_x;
    if (fabsf(x_value) > normal_epsilon) {
        return false;
    }

    auto y_value = lhs_y - rhs_y;
    if (fabsf(y_value) > normal_epsilon) {
        return false;
    }

    auto z_value = lhs_z - rhs_z;
    if (fabsf(z_value) > normal_epsilon) {
        return false;
    }

    auto distance_value = lhs_distance - rhs_distance;
    if (fabsf(distance_value) > distance_epsilon) {
        return false;
    }

    return true;
}

size_t BitmaskDecode(uint64_t* bitmap, size_t bitmapsize, uint32_t* out) {
    size_t   pos = 0;
    uint64_t bitset;
    for (size_t k = 0; k < bitmapsize; ++k) {
        bitset = bitmap[k];
        while (bitset != 0) {
            uint64_t      t = bitset & -bitset;
            unsigned long r = __builtin_ctzll(bitset);
            out[pos++]      = k * 64 + r;
            bitset ^= t;
        }
    }
    return pos;
}

void CompressPlanes() {
    for (int64_t global_index = 0; global_index < global_planes_count; global_index++) {
        FPlane  global_plane     = global_planes[global_index];
        int64_t compressed_index = 0;

        for (compressed_index = 0; compressed_index < compressed_planes_count; compressed_index++) {
            FPlane compressed_plane = compressed_planes[compressed_index];

            if (Compare(global_plane, compressed_plane, NORMAL_EPSILON, DISTANCE_EPSILON) == true) {
                break;
            }
        }

        if (compressed_index == compressed_planes_count) {
            compressed_planes[compressed_planes_count] = global_plane;
            compressed_planes_count++;
        }
    }
}

uint8_t ComparePlanes(FPlane comparend, FPlaneSIMDSet comparitor) {
    __m256i sign_mask_value  = _mm256_set1_epi32(0x80000000);
    __m256  sign_mask        = _mm256_castsi256_ps(sign_mask_value);
    __m256  normal_epsilon   = _mm256_set1_ps(NORMAL_EPSILON);
    __m256  distance_epsilon = _mm256_set1_ps(DISTANCE_EPSILON);

    __m256 comparend_x = _mm256_set1_ps(comparend.x);
    __m256 comparend_y = _mm256_set1_ps(comparend.y);
    __m256 comparend_z = _mm256_set1_ps(comparend.z);
    __m256 comparend_d = _mm256_set1_ps(comparend.distance);

    __m256 comparitor_x = _mm256_loadu_ps(comparitor.x);
    __m256 comparitor_y = _mm256_loadu_ps(comparitor.y);
    __m256 comparitor_z = _mm256_loadu_ps(comparitor.z);
    __m256 comparitor_d = _mm256_loadu_ps(comparitor.distance);

    __m256 difference_x = _mm256_sub_ps(comparend_x, comparitor_x);
    __m256 difference_y = _mm256_sub_ps(comparend_y, comparitor_y);
    __m256 difference_z = _mm256_sub_ps(comparend_z, comparitor_z);
    __m256 difference_d = _mm256_sub_ps(comparend_d, comparitor_d);

    __m256 absolute_x = _mm256_andnot_ps(sign_mask, difference_x);
    __m256 absolute_y = _mm256_andnot_ps(sign_mask, difference_y);
    __m256 absolute_z = _mm256_andnot_ps(sign_mask, difference_z);
    __m256 absolute_d = _mm256_andnot_ps(sign_mask, difference_d);

    __m256 comparison_x = _mm256_cmp_ps(absolute_x, normal_epsilon, _CMP_LE_OQ);
    __m256 comparison_y = _mm256_cmp_ps(absolute_y, normal_epsilon, _CMP_LE_OQ);
    __m256 comparison_z = _mm256_cmp_ps(absolute_z, normal_epsilon, _CMP_LE_OQ);
    __m256 comparison_d = _mm256_cmp_ps(absolute_d, distance_epsilon, _CMP_LE_OQ);

    int mask_x = _mm256_movemask_ps(comparison_x);
    int mask_y = _mm256_movemask_ps(comparison_y);
    int mask_z = _mm256_movemask_ps(comparison_z);
    int mask_d = _mm256_movemask_ps(comparison_d);

    int mask_final = mask_x & mask_y & mask_z & mask_d;

    return mask_final;
}

#include <chrono>

int main(int argc, char** argv) {
    /*
    uint64_t bitmap[] = {
      0b1000000000000000000000000000000000000000000000000000000000000001,
      0b1000000000000000000000000000000000000000000000000000000000000001,
    };

    uint32_t output[128] = {0};

    size_t result = BitmaskDecode(bitmap, 2, output);

    for (size_t index = 0; index < result; index++) {
        std::cout << output[index] << std::endl;
    }
    */

    std::string               runfiles_error {""};
    std::unique_ptr<Runfiles> runfiles {Runfiles::Create(argv[0], &runfiles_error)};

    GOOGLE_PROTOBUF_VERIFY_VERSION;

    if (runfiles == nullptr) {
        std::cout << "ERROR: Failed to initialize run-files : " << runfiles_error << std::endl;
    }

    std::string  map_path = runfiles->Rlocation("compusim/map/delta4.pb");
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
                    auto comparend_plane  = side.plane();
                    auto output_plane = &global_planes[global_planes_count];
                    global_planes_count++;

                    output_plane->x        = comparend_plane.normal_x();
                    output_plane->y        = comparend_plane.normal_y();
                    output_plane->z        = comparend_plane.normal_z();
                    output_plane->distance = comparend_plane.distance();

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

    using clock = std::chrono::system_clock;
    using duration = std::chrono::duration<double, std::micro>;

    const auto before = clock::now();
    CompressPlanes();
    const auto after = clock::now();
    const duration difference = after - before;

    std::cout << "TIME : " << difference.count() << std::endl;

    std::cout << "planes   : " << compressed_planes_count << std::endl;

    google::protobuf::ShutdownProtobufLibrary();
    return 0;
}
