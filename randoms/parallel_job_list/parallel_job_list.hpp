#pragma once

#include "shared.hpp"

#define REGISTER_PARALLEL_JOB(user_callback, name) static ParallelJobRegistration register_##user_callback((JobCallbackFunction)user_callback, name)

typedef void (*JobCallbackFunction)(void* user_data);

enum class JobSynchronizationType {
    None,
    Signal,
    Synchronize,
};

enum class JobListID {
    Renderer_FrontEnd = 0,
    Renderer_BackEnd  = 1,
    Utility           = 9,

    Max = 32
};

enum class JobListPriority { None, Low, Medium, High };

enum class JobListParallelism {
    Default        = -1,
    MaximumCores   = -2,
    MaximumThreads = -3,
};

class ParallelJobRegistration {
  public:
    ParallelJobRegistration(JobCallbackFunction user_callback, const char* name);
};

void RegisterJob(JobCallbackFunction user_callback, const char* name);

class ParallelJobList {
    friend class ParallelJobManagerLocal;

  public:
    void AddJob(JobCallbackFunction user_callback, void* user_data);

    void InsertSynchronizationPoint(JobSynchronizationType synchronization_type);

    void Submit(ParallelJobList* wait_for_job_list = nullptr, JobListParallelism parallelism = JobListParallelism::Default);
    bool IsSubmitted() const;

    void Wait();
    bool TryWait();

    unsigned int GetNumberOfExecutedJobs() const;
    unsigned int GetNumberOfSynchronizations() const;
    uint64_t     GetSubmitTime() const;
    uint64_t     GetStartTime() const;
    uint64_t     GetEndTime() const;
    uint64_t     GetWaitTime() const;
    uint64_t     GetTotalProcessingTime() const;
    uint64_t     GetTotalWastedTime() const;
    uint64_t     GetUnitProcessingTime(int unit) const;
    uint64_t     GetUnitWastedTime(int unit) const;

    JobListID GetID() const;

  private:
    class ParallelJobListThreads* job_list_threads;

    ParallelJobList(JobListID id, JobListPriority priority, unsigned int maximum_jobs, unsigned int maximum_synchronizations);
    ~ParallelJobList();
};

class ParallelJobManager {
  public:
    virtual ~ParallelJobManager() {
    }

    virtual void Start() = 0;
    virtual void Stop()  = 0;

    virtual ParallelJobList* AllocateJobList(JobListID id, JobListPriority priority, unsigned int maximum_jobs, unsigned int maximum_synchronizations) = 0;
    virtual void             FreeJobList(ParallelJobList* job_list)                                                                                    = 0;

    virtual void WaitForAllJobLists() = 0;

    virtual ParallelJobList* GetJobList(int index)                = 0;
    virtual int              GetNumberOfAllocatedJobLists() const = 0;
    virtual int              GetNumberOfFreeJobLists() const      = 0;

    virtual int GetNumberOfProcessingUnits() = 0;
};

extern ParallelJobManager* parallel_job_manager;
