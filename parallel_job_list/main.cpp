#include <iostream>
#include <immintrin.h>

#include "parallel_job_list/parallel_job_list.hpp"

#define ARRAY_SIZE(array) (sizeof(array) / sizeof(array[0]))

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
