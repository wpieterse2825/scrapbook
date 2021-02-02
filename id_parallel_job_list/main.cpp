#include <iostream>
#include <immintrin.h>

#include "id_parallel_job_list/parallel_job_list.hpp"

#define ARRAY_SIZE(array) (sizeof(array) / sizeof(array[0]))

struct FPlane {
    float x;
    float y;
    float z;
    float distance;
};

struct FPlaneSet {
    float x[32];
    float y[32];
    float z[32];
    float distance[32];

    FPlaneSet()
      : x {0.0f}
      , y {0.0f}
      , z {0.0f}
      , distance {0.0f} {
    }
};

FPlane planes[] = {
  {-1.0f, +0.0f, +0.0f, 10.0f},
  {+0.0f, +1.0f, +0.0f, 10.0f},
  {+1.0f, +0.0f, +0.0f, 10.0f},
  {+0.0f, -1.0f, +0.0f, 10.0f},
  {+0.0f, +0.0f, +1.0f, 10.0f},
  {+0.0f, +0.0f, -1.0f, 10.0f},
};

#define CROSS_PRODUCT(a, b)                                                                                                                                    \
    _mm256_permute4x64_pd(                                                                                                                                     \
      _mm256_sub_pd(_mm256_mul_pd(a, _mm256_permute4x64_pd(b, _MM_SHUFFLE(3, 0, 2, 1))), _mm256_mul_pd(b, _mm256_permute4x64_pd(a, _MM_SHUFFLE(3, 0, 2, 1)))), \
      _MM_SHUFFLE(3, 0, 2, 1))

inline __m256d CrossProduct(const __m256d& lhs, const __m256d& rhs) {
    return CROSS_PRODUCT(lhs, rhs);
}

inline __m256 Vector_Axis_Scale(__m256 scale, __m256 axis) {
    auto axis_scaled = _mm256_mul_ps(scale, axis);

    return axis_scaled;
}

inline void Vector_Scale(__m256 scale, __m256 axis_x, __m256 axis_y, __m256 axis_z, __m256& result_x, __m256& result_y, __m256& result_z) {
    result_x = Vector_Axis_Scale(scale, axis_x);
    result_y = Vector_Axis_Scale(scale, axis_y);
    result_z = Vector_Axis_Scale(scale, axis_z);
}

inline __m256 Vector_Axis_ScaledAdd(__m256 scale, __m256 lhs, __m256 rhs) {
    auto rhs_scaled = _mm256_mul_ps(scale, rhs);
    auto axis_add   = _mm256_add_ps(lhs, rhs_scaled);

    return axis_add;
}

inline void Vector_ScaledAdd(
  __m256 scale, __m256 lhs_x, __m256 lhs_y, __m256 lhs_z, __m256 rhs_x, __m256 rhs_y, __m256 rhs_z, __m256& result_x, __m256& result_y, __m256& result_z) {
    result_x = Vector_Axis_ScaledAdd(scale, lhs_x, rhs_x);
    result_y = Vector_Axis_ScaledAdd(scale, lhs_y, rhs_y);
    result_z = Vector_Axis_ScaledAdd(scale, lhs_z, rhs_z);
}

inline __m256 Vector_DotProduct(__m256 lhs_x, __m256 lhs_y, __m256 lhs_z, __m256 rhs_x, __m256 rhs_y, __m256 rhs_z) {
    auto x_multiplied = _mm256_mul_ps(lhs_x, rhs_x);
    auto y_multiplied = _mm256_mul_ps(lhs_y, rhs_y);
    auto z_multiplied = _mm256_mul_ps(lhs_z, rhs_z);

    auto xy_plus  = _mm256_add_ps(x_multiplied, y_multiplied);
    auto xyz_plus = _mm256_add_ps(xy_plus, z_multiplied);

    return xyz_plus;
}

inline __m256 Absolute(const __m256 input) {
    static const auto sign_mask = _mm256_set1_ps(-0.0f);

    return _mm256_andnot_ps(sign_mask, input);
}

inline void Vector_Normalize(const __m256 in_x, const __m256 in_y, const __m256 in_z, __m256& out_x, __m256& out_y, __m256& out_z) {
    auto x_times_x = _mm256_mul_ps(in_x, in_x);
    auto y_times_y = _mm256_mul_ps(in_y, in_y);
    auto z_times_z = _mm256_mul_ps(in_z, in_z);

    auto x_plus_y  = _mm256_add_ps(x_times_x, y_times_y);
    auto xy_plus_z = _mm256_add_ps(x_plus_y, z_times_z);

    auto length = _mm256_sqrt_ps(xy_plus_z);

    out_x = _mm256_div_ps(in_x, length);
    out_y = _mm256_div_ps(in_y, length);
    out_z = _mm256_div_ps(in_z, length);
}

inline void Vector_Normalize2(const __m256* in_x, const __m256* in_y, __m256* out_x, __m256* out_y) {
    // TODO(wpieterse): This should be part of a parameter somewhere, and not allocated like this.
    const uint64_t vectors   = 256;
    __m256*        x_times_x = static_cast<__m256*>(::malloc(sizeof(__m256) * vectors));
    __m256*        y_times_y = static_cast<__m256*>(::malloc(sizeof(__m256) * vectors));
    __m256*        x_plus_y  = static_cast<__m256*>(::malloc(sizeof(__m256) * vectors));
    __m256*        length    = static_cast<__m256*>(::malloc(sizeof(__m256) * vectors));

    for (uint64_t index = 0; index < vectors; index++) {
        x_times_x[index] = _mm256_mul_ps(in_x[index], in_x[index]);
        y_times_y[index] = _mm256_mul_ps(in_y[index], in_y[index]);
    }

    for (uint64_t index = 0; index < vectors; index++) {
        x_plus_y[index] = _mm256_add_ps(x_times_x[index], y_times_y[index]);
    }

    for (uint64_t index = 0; index < vectors; index++) {
        length[index] = _mm256_sqrt_ps(x_plus_y[index]);
    }

    for (uint64_t index = 0; index < vectors; index++) {
        out_x[index] = _mm256_div_ps(in_x[index], length[index]);
        out_y[index] = _mm256_div_ps(in_y[index], length[index]);
    }

    free(length);
    free(x_plus_y);
    free(y_times_y);
    free(x_times_x);
}

struct FNormalizeData {
    float x[16];
    float y[16];
    float z[16];

    float x_times_x[16];
    float y_times_y[16];
    float z_times_z[16];
    float x_plus_y[16];
    float xy_plus_z[16];
    float length[16];
};

static_assert(sizeof(FNormalizeData) == 576);

struct FPoint2D {
    __m256 x;
    __m256 y;
};

struct FPlane2D {
    __m256 x;
    __m256 y;
    __m256 distance;
};

FPlane2D Plane2DFromPoints(const FPoint2D start, const FPoint2D end) {
    FPlane2D result {};

    result.x = _mm256_sub_ps(start.y, end.y);
    result.y = _mm256_sub_ps(end.x, start.x);

    __m256 s_mul_p_x = _mm256_mul_ps(start.x, result.x);
    __m256 s_mul_p_y = _mm256_mul_ps(start.y, result.y);
    __m256 x_plus_y  = _mm256_add_ps(s_mul_p_x, s_mul_p_y);

    result.distance = _mm256_xor_ps(x_plus_y, _mm256_set1_ps(-0.0f));
    return result;
}

struct FPass {
    uint64_t value;

    FPass()
      : value {0} {
    }
};

#include <sys/types.h>
#include <unistd.h>
#include <sys/syscall.h>

void R_ExecutePass(FPass* data) {
    for (auto index = 0; index < 1024; index++) {
        data->value = syscall(__NR_gettid);
    }
}

int main() {
    FPass passes[8191] = {};

    RegisterJob((JobCallbackFunction)R_ExecutePass, "ExecutePass");

    parallel_job_manager->Start();

    auto job_list = parallel_job_manager->AllocateJobList(JobListID::Renderer_FrontEnd, JobListPriority::Medium, 8192, 0);

    auto start_time = Sys_Microseconds();
    for (size_t index = 0; index < ARRAY_SIZE(passes); index++) {
        auto pass = &passes[index];

        pass->value = index;
        job_list->AddJob((JobCallbackFunction)R_ExecutePass, pass);
    }

    job_list->Submit();
    job_list->Wait();
    auto end_time   = Sys_Microseconds();
    auto total_time = end_time - start_time;

    struct FThing {
        uint64_t id;
        uint64_t count;
    };

    FThing   things[16]   = {};
    uint64_t things_index = 0;

    for (size_t index = 0; index < ARRAY_SIZE(passes); index++) {
        auto found = false;
        auto value = passes[index].value;

        for (size_t tpz = 0; tpz < ARRAY_SIZE(things); tpz++) {
            if (things[tpz].id == value) {
                found = true;
            }
        }

        if (found == false) {
            things[things_index].id = value;
            things_index++;
        }
    }

    auto total = 0;

    for (size_t index = 0; index < ARRAY_SIZE(passes); index++) {
        auto value = passes[index].value;

        for (size_t tpz = 0; tpz < ARRAY_SIZE(things); tpz++) {
            if (things[tpz].id == value) {
                things[tpz].count++;
                break;
            }
        }

        total++;
    }

    for (size_t index = 0; index < things_index; index++) {
        std::cout << things[index].id << ": " << things[index].count << std::endl;
    }

    std::cout << std::endl;
    std::cout << "TOTAL : " << total << std::endl;
    std::cout << std::endl;
    std::cout << "TIME (ms): " << total_time / 1000 << std::endl;

    parallel_job_manager->FreeJobList(job_list);
    parallel_job_manager->Stop();
    return 0;
}
