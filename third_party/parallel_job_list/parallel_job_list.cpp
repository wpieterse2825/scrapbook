#include "third_party/parallel_job_list/shared.hpp"

#include "third_party/parallel_job_list/parallel_job_list.hpp"

#include "third_party/parallel_job_list/thread.hpp"

static uint64_t sys_microTimeBase = 0;

#define D3_CLOCK_TO_USE CLOCK_MONOTONIC

uint64_t Sys_Microseconds() {
    uint64_t        curtime;
    struct timespec ts;

    clock_gettime(D3_CLOCK_TO_USE, &ts);

    if (!sys_microTimeBase) {
        sys_microTimeBase = ts.tv_sec;
        return ts.tv_nsec / 1000;
    }

    curtime = (ts.tv_sec - sys_microTimeBase) * 1000000 + ts.tv_nsec / 1000;

    return curtime;
}

#define verify(x) ((x) ? true : false)

constexpr int MAXIMUM_JOB_REGISTRATIONS     = 128;
constexpr int MAXIMUM_THREADS               = 32;
constexpr int MAXIMUM_JOB_THREADS           = 12;
constexpr int INITIAL_NUMBER_OF_JOB_THREADS = 12;

struct RegisteredJob {
    JobCallbackFunction user_callback;
    const char*         name;
} registered_jobs[MAXIMUM_JOB_REGISTRATIONS];

struct ThreadJobListState {
    ThreadJobListState()
      : job_list(nullptr)
      , version(0xFFFFFFFF)
      , signal_index(0)
      , last_job_index(0)
      , next_job_index(-1) {
    }

    ThreadJobListState(int _version)
      : job_list(nullptr)
      , version(_version)
      , signal_index(0)
      , last_job_index(0)
      , next_job_index(-1) {
    }

    ParallelJobListThreads* job_list;
    int                     version;
    int                     signal_index;
    int                     last_job_index;
    int                     next_job_index;
};

struct ThreadStatistics {
    unsigned int number_of_executed_jobs;
    unsigned int number_of_executed_synchronizations;
    uint64_t     submit_time;
    uint64_t     start_time;
    uint64_t     end_time;
    uint64_t     wait_time;
    uint64_t     thread_execution_time[MAXIMUM_THREADS];
    uint64_t     thread_total_time[MAXIMUM_THREADS];
};

static int jobs_number_of_threads = INITIAL_NUMBER_OF_JOB_THREADS;
static int number_of_registered_jobs;

static bool IsRegisteredJob(JobCallbackFunction user_callback) {
    for (int index = 0; index < number_of_registered_jobs; index++) {
        if (registered_jobs[index].user_callback == user_callback) {
            return true;
        }
    }

    return false;
}

void RegisterJob(JobCallbackFunction user_callback, const char* name) {
    if (IsRegisteredJob(user_callback)) {
        return;
    }

    registered_jobs[number_of_registered_jobs].user_callback = user_callback;
    registered_jobs[number_of_registered_jobs].name          = name;
    number_of_registered_jobs++;
}

const char* GetJobName(JobCallbackFunction user_callback) {
    for (int index = 0; index < number_of_registered_jobs; index++) {
        if (registered_jobs[index].user_callback == user_callback) {
            return registered_jobs[index].name;
        }
    }

    return "unknown";
}

ParallelJobRegistration::ParallelJobRegistration(JobCallbackFunction user_callback, const char* name) {
    RegisterJob(user_callback, name);
}

class ParallelJobListThreads {
  public:
    ParallelJobListThreads(JobListID id, JobListPriority priority, unsigned int maximum_jobs, unsigned int maximum_synchronizations);
    ~ParallelJobListThreads();

    void AddJob(JobCallbackFunction user_callback, void* data);

    void InsertSynchronizationPoint(JobSynchronizationType synchronization_type);

    void Submit(ParallelJobListThreads* wait_for_job_list, JobListParallelism parallelism);
    bool IsSubmitted() const;

    int RunJobs(unsigned int thread_number, ThreadJobListState& state, bool is_single_job);

    void Wait();
    bool TryWait();

    bool WaitForOtherJobList();

    unsigned int GetNumberOfExecutedJobs() const {
        return thread_statistics.number_of_executed_jobs;
    }

    unsigned int GetNumberOfSynchronizations() const {
        return thread_statistics.number_of_executed_synchronizations;
    }

    uint64_t GetSubmitTime() const {
        return thread_statistics.submit_time;
    }

    uint64_t GetStartTime() const {
        return thread_statistics.start_time;
    }

    uint64_t GetEndTime() const {
        return thread_statistics.end_time;
    }

    uint64_t GetWaitTime() const {
        return thread_statistics.wait_time;
    }

    uint64_t GetTotalProcessingTime() const;
    uint64_t GetTotalWastedTime() const;
    uint64_t GetUnitProcessingTime(int unit) const;
    uint64_t GetUnitWastedTime(int unit) const;

    JobListID GetID() const {
        return list_id;
    }

    JobListPriority GetPriority() const {
        return list_priority;
    }

    int GetVersion() {
        return version.GetValue();
    }

    enum runResult_t { RUN_OK = 0, RUN_PROGRESS = BIT(0), RUN_DONE = BIT(1), RUN_STALLED = BIT(2) };

  private:
    struct JobListJob {
        JobCallbackFunction user_callback;
        void*               data;
        int                 executed;
    };

    static const int MAXIMUM_DONE_GUARDS = 4;

    bool                                    threaded;
    bool                                    done;
    bool                                    has_signal;
    JobListID                               list_id;
    JobListPriority                         list_priority;
    unsigned int                            maximum_jobs;
    unsigned int                            maximum_synchronizations;
    unsigned int                            number_of_synchronizations;
    int                                     last_signal_job;
    InterlockedInteger*                     wait_for_guard;
    InterlockedInteger                      done_guards[MAXIMUM_DONE_GUARDS];
    int                                     current_done_guard;
    InterlockedInteger                      version;
    idList<JobListJob, TAG_JOBLIST>         job_list;
    idList<InterlockedInteger, TAG_JOBLIST> signal_job_count;
    InterlockedInteger                      current_job;
    InterlockedInteger                      fetch_lock;
    InterlockedInteger                      number_of_threads_executing;

    ThreadStatistics deferred_thread_statistics;
    ThreadStatistics thread_statistics;

    int RunJobsInternal(unsigned int thread_number, ThreadJobListState& state, bool is_single_job);

    static void Nop(void* data) {
    }

    static int JOB_SIGNAL;
    static int JOB_SYNCHRONIZE;
    static int JOB_LIST_DONE;
};

int ParallelJobListThreads::JOB_SIGNAL;
int ParallelJobListThreads::JOB_SYNCHRONIZE;
int ParallelJobListThreads::JOB_LIST_DONE;

ParallelJobListThreads::ParallelJobListThreads(JobListID id, JobListPriority priority, unsigned int maximum_jobs, unsigned int maximum_synchronizations)
  : threaded(true)
  , done(true)
  , has_signal(false)
  , list_id(id)
  , list_priority(priority)
  , number_of_synchronizations(0)
  , last_signal_job(0)
  , wait_for_guard(nullptr)
  , current_done_guard(0)
  , job_list() {
    assert(list_priority != JobListPriority::None);

    this->maximum_jobs             = maximum_jobs;
    this->maximum_synchronizations = maximum_synchronizations;

    job_list.AssureSize(maximum_jobs + maximum_synchronizations * 2 + 1);
    job_list.SetNum(0);

    signal_job_count.AssureSize(maximum_synchronizations + 1); // need one extra for submit
    signal_job_count.SetNum(0);

    memset(&deferred_thread_statistics, 0, sizeof(ThreadStatistics));
    memset(&thread_statistics, 0, sizeof(ThreadStatistics));
}

ParallelJobListThreads::~ParallelJobListThreads() {
    Wait();
}

void ParallelJobListThreads::AddJob(JobCallbackFunction user_callback, void* data) {
    assert(done);
#if defined(_DEBUG)
    // make sure there isn't already a job with the same user_callback and data in the list
    if (job_list.Num() < 1000) // don't do this N^2 slow check on big lists
    {
        for (int index = 0; index < job_list.Num(); index++) {
            assert(job_list[index].user_callback != user_callback || job_list[index].data != data);
        }
    }
#endif

    if (1) // JDC: this never worked in tech5!  !job_list.IsFull() ) {
    {
        JobListJob& job   = job_list.Alloc();
        job.user_callback = user_callback;
        job.data          = data;
        job.executed      = 0;
    } else {
        int currentJobCount[MAXIMUM_JOB_REGISTRATIONS] = {};

        for (int index = 0; index < job_list.Num(); ++index) {
            const char* jobName = GetJobName(job_list[index].user_callback);
            for (int j = 0; j < number_of_registered_jobs; ++j) {
                if (jobName == registered_jobs[j].name) {
                    currentJobCount[j]++;
                    break;
                }
            }
        }

        for (int index = 0; index < number_of_registered_jobs; ++index) {
            if (currentJobCount[index] > 0) {
                printf("Job: %s, # %d", registered_jobs[index].name, currentJobCount[index]);
            }
        }

        printf("Can't add job '%s', too many jobs %d", GetJobName(user_callback), job_list.Num());
    }
}

void ParallelJobListThreads::InsertSynchronizationPoint(JobSynchronizationType synchronization_type) {
    assert(done);

    switch (synchronization_type) {
        case JobSynchronizationType::Signal: {
            assert(!has_signal);
            if (job_list.Num()) {
                assert(!has_signal);

                signal_job_count.Alloc();
                signal_job_count[signal_job_count.Num() - 1].SetValue(job_list.Num() - last_signal_job);

                last_signal_job = job_list.Num();

                JobListJob& job   = job_list.Alloc();
                job.user_callback = Nop;
                job.data          = &JOB_SIGNAL;

                has_signal = true;
            }

            break;
        }
        case JobSynchronizationType::Synchronize: {
            if (has_signal) {
                JobListJob& job   = job_list.Alloc();
                job.user_callback = Nop;
                job.data          = &JOB_SYNCHRONIZE;

                has_signal = false;

                number_of_synchronizations++;
            }

            break;
        }
        default:
            break;
    }
}

void SubmitJobList(ParallelJobListThreads* job_list, JobListParallelism parallelism);

void ParallelJobListThreads::Submit(ParallelJobListThreads* wait_for_job_list, JobListParallelism parallelism) {
    assert(done);
    assert(number_of_synchronizations <= maximum_synchronizations);
    assert((unsigned int)job_list.Num() <= maximum_jobs + number_of_synchronizations * 2);
    assert(fetch_lock.GetValue() == 0);

    done = false;
    current_job.SetValue(0);

    memset(&deferred_thread_statistics, 0, sizeof(deferred_thread_statistics));
    deferred_thread_statistics.number_of_executed_jobs             = job_list.Num() - number_of_synchronizations * 2;
    deferred_thread_statistics.number_of_executed_synchronizations = number_of_synchronizations;
    deferred_thread_statistics.submit_time                         = Sys_Microseconds();
    deferred_thread_statistics.start_time                          = 0;
    deferred_thread_statistics.end_time                            = 0;
    deferred_thread_statistics.wait_time                           = 0;

    if (job_list.Num() == 0) {
        return;
    }

    if (wait_for_job_list != nullptr) {
        wait_for_guard = &wait_for_job_list->done_guards[wait_for_job_list->current_done_guard];
    } else {
        wait_for_guard = nullptr;
    }

    current_done_guard = (current_done_guard + 1) & (MAXIMUM_DONE_GUARDS - 1);
    done_guards[current_done_guard].SetValue(1);

    signal_job_count.Alloc();
    signal_job_count[signal_job_count.Num() - 1].SetValue(job_list.Num() - last_signal_job);

    JobListJob& job   = job_list.Alloc();
    job.user_callback = Nop;
    job.data          = &JOB_LIST_DONE;

    if (threaded) {
        SubmitJobList(this, parallelism);
    } else {
        ThreadJobListState state(GetVersion());
        RunJobs(0, state, false);
    }
}

void ParallelJobListThreads::Wait() {
    if (job_list.Num() > 0) {
        if (!verify(!done && signal_job_count.Num() > 0)) {
            return;
        }

        bool     waited    = false;
        uint64_t waitStart = Sys_Microseconds();
        while (signal_job_count[signal_job_count.Num() - 1].GetValue() > 0) {
            Sys_Yield();
            waited = true;
        }

        version.Increment();
        while (number_of_threads_executing.GetValue() > 0) {
            Sys_Yield();
            waited = true;
        }

        uint64_t waitEnd = Sys_Microseconds();

        job_list.SetNum(0);
        signal_job_count.SetNum(0);
        number_of_synchronizations           = 0;
        last_signal_job                      = 0;
        deferred_thread_statistics.wait_time = waited ? (waitEnd - waitStart) : 0;
    }

    memcpy(&thread_statistics, &deferred_thread_statistics, sizeof(thread_statistics));
    done = true;
}

bool ParallelJobListThreads::TryWait() {
    if (job_list.Num() == 0 || signal_job_count[signal_job_count.Num() - 1].GetValue() <= 0) {
        Wait();
        return true;
    }

    return false;
}

bool ParallelJobListThreads::IsSubmitted() const {
    return !done;
}

uint64_t ParallelJobListThreads::GetTotalProcessingTime() const {
    uint64_t total = 0;
    for (int unit = 0; unit < MAXIMUM_THREADS; unit++) {
        total += thread_statistics.thread_execution_time[unit];
    }

    return total;
}

uint64_t ParallelJobListThreads::GetTotalWastedTime() const {
    uint64_t total = 0;
    for (int unit = 0; unit < MAXIMUM_THREADS; unit++) {
        total += thread_statistics.thread_total_time[unit] - thread_statistics.thread_execution_time[unit];
    }

    return total;
}

uint64_t ParallelJobListThreads::GetUnitProcessingTime(int unit) const {
    if (unit < 0 || unit >= MAXIMUM_THREADS) {
        return 0;
    }

    return thread_statistics.thread_execution_time[unit];
}

uint64_t ParallelJobListThreads::GetUnitWastedTime(int unit) const {
    if (unit < 0 || unit >= MAXIMUM_THREADS) {
        return 0;
    }

    return thread_statistics.thread_total_time[unit] - thread_statistics.thread_execution_time[unit];
}

#ifndef _DEBUG
volatile float               longJobTime;
volatile JobCallbackFunction longJobFunc;
volatile void*               longJobData;
#endif

int ParallelJobListThreads::RunJobsInternal(unsigned int thread_number, ThreadJobListState& state, bool is_single_job) {
    if (state.version != version.GetValue()) {
        return RUN_DONE;
    }

    assert(thread_number < MAXIMUM_THREADS);
    if (deferred_thread_statistics.start_time == 0) {
        deferred_thread_statistics.start_time = Sys_Microseconds();
    }

    int result = RUN_OK;

    do {
        for (; state.last_job_index < (int)current_job.GetValue() && state.last_job_index < job_list.Num(); state.last_job_index++) {
            if (job_list[state.last_job_index].data == &JOB_SIGNAL) {
                state.signal_index++;
                assert(state.signal_index < signal_job_count.Num());
            } else if (job_list[state.last_job_index].data == &JOB_SYNCHRONIZE) {
                assert(state.signal_index > 0);
                if (signal_job_count[state.signal_index - 1].GetValue() > 0) {
                    return (result | RUN_STALLED);
                }
            } else if (job_list[state.last_job_index].data == &JOB_LIST_DONE) {
                if (signal_job_count[signal_job_count.Num() - 1].GetValue() > 0) {
                    return (result | RUN_STALLED);
                }
            }
        }

        if (fetch_lock.Increment() == 1) {
            state.next_job_index = current_job.Increment() - 1;
            for (; state.last_job_index <= state.next_job_index && state.last_job_index < job_list.Num(); state.last_job_index++) {
                if (job_list[state.last_job_index].data == &JOB_SIGNAL) {
                    state.signal_index++;
                    assert(state.signal_index < signal_job_count.Num());
                } else if (job_list[state.last_job_index].data == &JOB_SYNCHRONIZE) {
                    assert(state.signal_index > 0);

                    if (signal_job_count[state.signal_index - 1].GetValue() > 0) {
                        current_job.Decrement();
                        fetch_lock.Decrement();
                        return (result | RUN_STALLED);
                    }
                } else if (job_list[state.last_job_index].data == &JOB_LIST_DONE) {
                    if (signal_job_count[signal_job_count.Num() - 1].GetValue() > 0) {
                        current_job.Decrement();
                        fetch_lock.Decrement();
                        return (result | RUN_STALLED);
                    }

                    done_guards[current_done_guard].Decrement();
                }
            }

            fetch_lock.Decrement();
        } else {
            fetch_lock.Decrement();
            return (result | RUN_STALLED);
        }

        if (state.next_job_index >= job_list.Num()) {
            return (result | RUN_DONE);
        }

        {
            uint64_t jobStart = Sys_Microseconds();

            job_list[state.next_job_index].user_callback(job_list[state.next_job_index].data);
            job_list[state.next_job_index].executed = 1;

            uint64_t jobEnd = Sys_Microseconds();
            deferred_thread_statistics.thread_execution_time[thread_number] += jobEnd - jobStart;

#ifndef _DEBUG
            if (10000 > 0) {
                if (jobEnd - jobStart > 100000 && GetID() != JobListID::Utility) {
                    longJobTime         = (jobEnd - jobStart) * (1.0f / 1000.0f);
                    longJobFunc         = job_list[state.next_job_index].user_callback;
                    longJobData         = job_list[state.next_job_index].data;
                    const char* jobName = GetJobName(job_list[state.next_job_index].user_callback);
                    // const char* jobListName = GetJobListName(GetID());
                    printf("%1.1f milliseconds for a single '%s' job on thread %d\n",
                           longJobTime,
                           jobName,
                           // jobListName,
                           thread_number);
                }
            }
#endif
        }

        result |= RUN_PROGRESS;
        if (signal_job_count[state.signal_index].Decrement() == 0) {
            if (state.signal_index == signal_job_count.Num() - 1) {
                deferred_thread_statistics.end_time = Sys_Microseconds();
                return (result | RUN_DONE);
            }
        }
    } while (!is_single_job);

    return result;
}

int ParallelJobListThreads::RunJobs(unsigned int thread_number, ThreadJobListState& state, bool is_single_job) {
    uint64_t start = Sys_Microseconds();

    number_of_threads_executing.Increment();
    int result = RunJobsInternal(thread_number, state, is_single_job);
    number_of_threads_executing.Decrement();

    deferred_thread_statistics.thread_total_time[thread_number] += Sys_Microseconds() - start;
    return result;
}

bool ParallelJobListThreads::WaitForOtherJobList() {
    if (wait_for_guard != nullptr) {
        if (wait_for_guard->GetValue() > 0) {
            return true;
        }
    }

    return false;
}

ParallelJobList::ParallelJobList(JobListID id, JobListPriority priority, unsigned int maximum_jobs, unsigned int maximum_synchronizations) {
    assert(priority > JobListPriority::None);

    this->job_list_threads = new ParallelJobListThreads(id, priority, maximum_jobs, maximum_synchronizations);
}

ParallelJobList::~ParallelJobList() {
    delete job_list_threads;
}

void ParallelJobList::AddJob(JobCallbackFunction user_callback, void* data) {
    assert(IsRegisteredJob(user_callback));

    job_list_threads->AddJob(user_callback, data);
}

void ParallelJobList::InsertSynchronizationPoint(JobSynchronizationType synchronization_type) {
    job_list_threads->InsertSynchronizationPoint(synchronization_type);
}

void ParallelJobList::Wait() {
    if (job_list_threads != nullptr) {
        job_list_threads->Wait();
    }
}

bool ParallelJobList::TryWait() {
    bool done = true;
    if (job_list_threads != nullptr) {
        done &= job_list_threads->TryWait();
    }

    return done;
}

void ParallelJobList::Submit(ParallelJobList* wait_for_job_list, JobListParallelism parallelism) {
    assert(wait_for_job_list != this);

    job_list_threads->Submit((wait_for_job_list != nullptr) ? wait_for_job_list->job_list_threads : nullptr, parallelism);
}

bool ParallelJobList::IsSubmitted() const {
    return job_list_threads->IsSubmitted();
}

unsigned int ParallelJobList::GetNumberOfExecutedJobs() const {
    return job_list_threads->GetNumberOfExecutedJobs();
}

unsigned int ParallelJobList::GetNumberOfSynchronizations() const {
    return job_list_threads->GetNumberOfSynchronizations();
}

uint64_t ParallelJobList::GetSubmitTime() const {
    return job_list_threads->GetSubmitTime();
}

uint64_t ParallelJobList::GetStartTime() const {
    return job_list_threads->GetStartTime();
}

uint64_t ParallelJobList::GetEndTime() const {
    return job_list_threads->GetEndTime();
}

uint64_t ParallelJobList::GetWaitTime() const {
    return job_list_threads->GetWaitTime();
}

uint64_t ParallelJobList::GetTotalProcessingTime() const {
    return job_list_threads->GetTotalProcessingTime();
}

uint64_t ParallelJobList::GetTotalWastedTime() const {
    return job_list_threads->GetTotalWastedTime();
}

uint64_t ParallelJobList::GetUnitProcessingTime(int unit) const {
    return job_list_threads->GetUnitProcessingTime(unit);
}

uint64_t ParallelJobList::GetUnitWastedTime(int unit) const {
    return job_list_threads->GetUnitWastedTime(unit);
}

JobListID ParallelJobList::GetID() const {
    return job_list_threads->GetID();
}

const int JOB_THREAD_STACK_SIZE = 256 * 1024;

struct ThreadJobList {
    ParallelJobListThreads* job_list;
    int                     version;
};

bool jobs_prioritize = true;

class JobThread : public Thread {
  public:
    JobThread();
    ~JobThread();

    void Start(unsigned int thread_number);

    void AddJobList(ParallelJobListThreads* job_list);

  private:
    ThreadJobList job_lists[(size_t)JobListID::Max]; // cyclic buffer with job lists
    unsigned int  first_job_list;                    // index of the last job list the thread grabbed
    unsigned int  last_job_list;                     // index where the next job list to work on will be added
    Mutex         add_job_lock;

    unsigned int thread_number;

    virtual int Run();
};

JobThread::JobThread()
  : first_job_list(0)
  , last_job_list(0)
  , thread_number(0) {
}

JobThread::~JobThread() {
}

void JobThread::Start(unsigned int thread_number) {
    char name[16] = {0};

    this->thread_number = thread_number;

    snprintf(name, 16, "JLProc_%d", thread_number);
    StartWorkerThread(name, ThreadPriority::Normal, JOB_THREAD_STACK_SIZE);
}

void JobThread::AddJobList(ParallelJobListThreads* job_list) {
    add_job_lock.Lock();
    while (last_job_list - first_job_list >= ((int)JobListID::Max)) {
        Sys_Yield();
    }

    assert(last_job_list - first_job_list < ((int)JobListID::Max));
    job_lists[last_job_list & (((int)JobListID::Max) - 1)].job_list = job_list;
    job_lists[last_job_list & (((int)JobListID::Max) - 1)].version  = job_list->GetVersion();
    last_job_list++;
    add_job_lock.Unlock();
}

int JobThread::Run() {
    ThreadJobListState threadJobListState[((size_t)JobListID::Max)];
    int                numJobLists        = 0;
    int                lastStalledJobList = -1;

    while (!IsTerminating()) {
        if (numJobLists < ((int)JobListID::Max) && first_job_list < last_job_list) {
            threadJobListState[numJobLists].job_list       = job_lists[first_job_list & (((int)JobListID::Max) - 1)].job_list;
            threadJobListState[numJobLists].version        = job_lists[first_job_list & (((int)JobListID::Max) - 1)].version;
            threadJobListState[numJobLists].signal_index   = 0;
            threadJobListState[numJobLists].last_job_index = 0;
            threadJobListState[numJobLists].next_job_index = -1;
            numJobLists++;
            first_job_list++;
        }

        if (numJobLists == 0) {
            break;
        }

        int             currentJobList = 0;
        JobListPriority priority       = JobListPriority::None;
        if (lastStalledJobList < 0) {
            for (int index = 0; index < numJobLists; index++) {
                if (threadJobListState[index].job_list->GetPriority() > priority && !threadJobListState[index].job_list->WaitForOtherJobList()) {
                    priority       = threadJobListState[index].job_list->GetPriority();
                    currentJobList = index;
                }
            }
        } else {
            currentJobList = lastStalledJobList;
            priority       = threadJobListState[lastStalledJobList].job_list->GetPriority();

            for (int index = 0; index < numJobLists; index++) {
                if (index != lastStalledJobList && threadJobListState[index].job_list->GetPriority() >= priority &&
                    !threadJobListState[index].job_list->WaitForOtherJobList()) {
                    priority       = threadJobListState[index].job_list->GetPriority();
                    currentJobList = index;
                }
            }
        }

        bool is_single_job = (priority == JobListPriority::High) ? false : jobs_prioritize;
        int  result        = threadJobListState[currentJobList].job_list->RunJobs(thread_number, threadJobListState[currentJobList], is_single_job);
        if ((result & ParallelJobListThreads::RUN_DONE) != 0) {
            for (int index = currentJobList; index < numJobLists - 1; index++) {
                threadJobListState[index] = threadJobListState[index + 1];
            }

            numJobLists--;
            lastStalledJobList = -1;
        } else if ((result & ParallelJobListThreads::RUN_STALLED) != 0) {
            if (currentJobList == lastStalledJobList) {
                if ((result & ParallelJobListThreads::RUN_PROGRESS) == 0) {
                    Sys_Yield();
                }
            }

            lastStalledJobList = currentJobList;
        } else {
            lastStalledJobList = -1;
        }
    }

    return 0;
}

class ParallelJobManagerLocal : public ParallelJobManager {
  public:
    virtual ~ParallelJobManagerLocal() {
    }

    virtual void Start();
    virtual void Stop();

    virtual ParallelJobList* AllocateJobList(JobListID id, JobListPriority priority, unsigned int maximum_jobs, unsigned int maximum_synchronizations);
    virtual void             FreeJobList(ParallelJobList* job_list);

    virtual int              GetNumberOfAllocatedJobLists() const;
    virtual int              GetNumberOfFreeJobLists() const;
    virtual ParallelJobList* GetJobList(int index);

    virtual int GetNumberOfProcessingUnits();

    virtual void WaitForAllJobLists();

    void Submit(ParallelJobListThreads* job_list, JobListParallelism parallelism);

  private:
    JobThread                                                threads[MAXIMUM_JOB_THREADS];
    unsigned int                                             maximum_threads;
    int                                                      number_of_physical_cpu_cores;
    int                                                      number_of_logical_cpu_cores;
    int                                                      number_of_cpu_packages;
    idStaticList<ParallelJobList*, ((size_t)JobListID::Max)> job_lists;
};

ParallelJobManagerLocal parallel_job_manager_local;
ParallelJobManager*     parallel_job_manager = &parallel_job_manager_local;

void SubmitJobList(ParallelJobListThreads* job_list, JobListParallelism parallelism) {
    parallel_job_manager_local.Submit(job_list, parallelism);
}

void ParallelJobManagerLocal::Start() {
    for (int index = 0; index < MAXIMUM_JOB_THREADS; index++) {
        threads[index].Start(index);
    }

    maximum_threads = jobs_number_of_threads;

    // TODO(wpieterse): Work this out.
    number_of_physical_cpu_cores = 4;
    number_of_logical_cpu_cores  = 8;
    number_of_cpu_packages       = 1;
}

void ParallelJobManagerLocal::Stop() {
    for (int index = 0; index < MAXIMUM_JOB_THREADS; index++) {
        threads[index].StopThread();
    }
}

ParallelJobList*
ParallelJobManagerLocal::AllocateJobList(JobListID id, JobListPriority priority, unsigned int maximum_jobs, unsigned int maximum_synchronizations) {
    ParallelJobList* job_list = new ParallelJobList(id, priority, maximum_jobs, maximum_synchronizations);

    job_lists.Append(job_list);
    return job_list;
}

void ParallelJobManagerLocal::FreeJobList(ParallelJobList* job_list) {
    if (job_list == nullptr) {
        return;
    }

    for (unsigned int index = 0; index < maximum_threads; index++) {
        threads[index].WaitForThread();
    }

    int index = job_lists.FindIndex(job_list);
    assert(index >= 0 && job_lists[index] == job_list);
    job_lists[index]->Wait();

    delete job_lists[index];

    job_lists.RemoveIndexFast(index);
}

int ParallelJobManagerLocal::GetNumberOfAllocatedJobLists() const {
    return job_lists.Num();
}

int ParallelJobManagerLocal::GetNumberOfFreeJobLists() const {
    return ((int)JobListID::Max) - job_lists.Num();
}

ParallelJobList* ParallelJobManagerLocal::GetJobList(int index) {
    return job_lists[index];
}

int ParallelJobManagerLocal::GetNumberOfProcessingUnits() {
    return maximum_threads;
}

void ParallelJobManagerLocal::WaitForAllJobLists() {
    for (int index = 0; index < job_lists.Num(); index++) {
        job_lists[index]->Wait();
    }
}

void ParallelJobManagerLocal::Submit(ParallelJobListThreads* job_list, JobListParallelism parallelism) {
    /*
    if (jobs_number_of_threads.IsModified()) {
        maximum_threads = idMath::ClampInt(0, MAXIMUM_JOB_THREADS, jobs_number_of_threads.GetInteger());
        jobs_number_of_threads.ClearModified();
    }
    */

    int number_of_threads = maximum_threads;
    if (parallelism == JobListParallelism::Default) {
        number_of_threads = maximum_threads;
    } else if (parallelism == JobListParallelism::MaximumCores) {
        number_of_threads = number_of_logical_cpu_cores;
    } else if (parallelism == JobListParallelism::MaximumThreads) {
        number_of_threads = MAXIMUM_JOB_THREADS;
    } else if (((int)parallelism) > MAXIMUM_JOB_THREADS) {
        number_of_threads = MAXIMUM_JOB_THREADS;
    } else {
        number_of_threads = ((int)parallelism);
    }

    if (number_of_threads <= 0) {
        ThreadJobListState state(job_list->GetVersion());
        job_list->RunJobs(0, state, false);
        return;
    }

    for (int index = 0; index < number_of_threads; index++) {
        threads[index].AddJobList(job_list);
        threads[index].SignalWork();
    }
}
