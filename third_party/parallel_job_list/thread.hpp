#pragma once

#include "third_party/parallel_job_list/shared.hpp"
#include "third_party/parallel_job_list/list.hpp"

#include <pthread.h>

#define DEFAULT_THREAD_STACK_SIZE (256 * 1024)

#define SYS_MEMORYBARRIER                                                                                                                                      \
    asm volatile("" ::: "memory");                                                                                                                             \
    __sync_synchronize()

enum class ThreadPriority {
    Lowest,
    BelowNormal,
    Normal,
    AboveNormal,
    Highest,
};

typedef uint32_t (*ThreadCallbackFunction)(void*);

uintptr_t Sys_CreateThread(ThreadCallbackFunction user_callback,
                           void*                  user_parameter,
                           ThreadPriority         priority,
                           const char*            name,
                           int32_t                stack_size      = DEFAULT_THREAD_STACK_SIZE,
                           bool                   start_suspended = false);

void      Sys_DestroyThread(uintptr_t thread_handle);
uintptr_t Sys_GetCurrentThreadID();
void      Sys_SetCurrentThreadName(const char* name);

void Sys_Yield();

struct SignalHandle {
    pthread_cond_t  cond;
    pthread_mutex_t mutex;
    int32_t         waiting; // number of threads waiting for a signal
    bool            is_manual_reset;
    bool            signaled; // is it signaled right now?
};

void Sys_SignalCreate(SignalHandle& handle, bool is_manual_reset);
void Sys_SignalDestroy(SignalHandle& handle);
void Sys_SignalRaise(SignalHandle& handle);
void Sys_SignalClear(SignalHandle& handle);
bool Sys_SignalWait(SignalHandle& handle, int32_t timeout);

typedef pthread_mutex_t MutexHandle;

void Sys_MutexCreate(MutexHandle& handle);
void Sys_MutexDestroy(MutexHandle& handle);
bool Sys_MutexLock(MutexHandle& handle, bool is_blocking);
void Sys_MutexUnlock(MutexHandle& handle);

typedef int32_t InterlockedHandle;

InterlockedHandle Sys_InterlockedIncrement(InterlockedHandle& value);
InterlockedHandle Sys_InterlockedDecrement(InterlockedHandle& value);
InterlockedHandle Sys_InterlockedAdd(InterlockedHandle& value, InterlockedHandle index);
InterlockedHandle Sys_InterlockedSub(InterlockedHandle& value, InterlockedHandle index);
InterlockedHandle Sys_InterlockedExchange(InterlockedHandle& value, InterlockedHandle exchange);
InterlockedHandle Sys_InterlockedCompareExchange(InterlockedHandle& value, InterlockedHandle comparand, InterlockedHandle exchange);

void* Sys_InterlockedExchangePointer(void*& value, void* exchange);
void* Sys_InterlockedCompareExchangePointer(void*& value, void* comparand, void* exchange);

class ThreadLocalStorage {
  public:
    ThreadLocalStorage() {
        pthread_key_create(&key, nullptr);
    }

    ThreadLocalStorage(const ptrdiff_t& value) {
        pthread_key_create(&key, nullptr);
        pthread_setspecific(key, (const void*)value);
    }

    ~ThreadLocalStorage() {
        pthread_key_delete(key);
    }

    operator ptrdiff_t() {
        return (ptrdiff_t)pthread_getspecific(key);
    }

    const ptrdiff_t& operator=(const ptrdiff_t& value) {
        pthread_setspecific(key, (const void*)value);
        return value;
    }

    pthread_key_t key;
};

class Mutex {
  public:
    Mutex() {
        Sys_MutexCreate(handle);
    }

    ~Mutex() {
        Sys_MutexDestroy(handle);
    }

    bool Lock(bool is_blocking = true) {
        return Sys_MutexLock(handle, is_blocking);
    }

    void Unlock() {
        Sys_MutexUnlock(handle);
    }

  private:
    MutexHandle handle;

    Mutex(const Mutex&) {
    }

    void operator=(const Mutex&) {
    }
};

class ScopedMutexLock {
  public:
    ScopedMutexLock(Mutex& input_mutex)
      : mutex {&input_mutex} {
        mutex->Lock();
    }

    ~ScopedMutexLock() {
        mutex->Unlock();
    }

  private:
    Mutex* mutex;
};

class Signal {
  public:
    static const int32_t WAIT_INFINITE = -1;

    Signal(bool is_manual_reset = false) {
        Sys_SignalCreate(handle, is_manual_reset);
    }

    ~Signal() {
        Sys_SignalDestroy(handle);
    }

    void Raise() {
        Sys_SignalRaise(handle);
    }

    void Clear() {
        Sys_SignalClear(handle);
    }

    bool Wait(int32_t timeout = WAIT_INFINITE) {
        return Sys_SignalWait(handle, timeout);
    }

  private:
    SignalHandle handle;

    Signal(const Signal&) {
    }

    void operator=(const Signal&) {
    }
};

class InterlockedInteger {
  public:
    InterlockedInteger()
      : value {0} {
    }

    int32_t Increment() {
        return Sys_InterlockedIncrement(value);
    }

    int32_t Decrement() {
        return Sys_InterlockedDecrement(value);
    }

    int32_t Add(int32_t input_value) {
        return Sys_InterlockedAdd(value, (InterlockedHandle)input_value);
    }

    int32_t Subtract(int32_t input_value) {
        return Sys_InterlockedSub(value, (InterlockedHandle)input_value);
    }

    int32_t GetValue() const {
        return value;
    }

    void SetValue(int32_t input_value) {
        value = (InterlockedHandle)input_value;
    }

  private:
    InterlockedHandle value;
};

template <typename ElementType>
class InterlockedPointer {
  public:
    InterlockedPointer()
      : value {nullptr} {
    }

    ElementType* Set(ElementType* input_value) {
        return (ElementType*)Sys_InterlockedExchangePointer((void*&)value, input_value);
    }

    ElementType* CompareExchange(ElementType* compare_value, ElementType* input_value) {
        return (ElementType*)Sys_InterlockedCompareExchangePointer((void*&)value, compare_value, input_value);
    }

    ElementType* Get() const {
        return value;
    }

  private:
    ElementType* value;
};

class Thread {
  public:
    Thread();
    virtual ~Thread();

    const char* GetName() const {
        return name;
    }

    uintptr_t GetThreadHandle() const {
        return thread_handle;
    }

    bool IsRunning() const {
        return is_running;
    }

    bool IsTerminating() const {
        return is_terminating;
    }

    bool StartThread(const char* name, ThreadPriority priority = ThreadPriority::Normal, int32_t stack_size = DEFAULT_THREAD_STACK_SIZE);

    bool StartWorkerThread(const char* name, ThreadPriority priority = ThreadPriority::Normal, int32_t stack_size = DEFAULT_THREAD_STACK_SIZE);

    void StopThread(bool wait = true);

    void WaitForThread();

    void SignalWork();

    bool IsWorkDone();

  protected:
    virtual int32_t Run();

  private:
    const char*   name;
    uintptr_t     thread_handle;
    bool          is_worker_thread;
    bool          is_running;
    volatile bool is_terminating;
    volatile bool has_more_work;
    Signal        signal_work_done;
    Signal        signal_has_more_work;
    Mutex         signal_lock;

    static int32_t SysstemThreadProcedure(Thread* thread);

    Thread(const Thread&) {
    }

    void operator=(const Thread&) {
    }
};

template <class ThreadType>
class ThreadWorkerGroup {
  public:
    ThreadWorkerGroup(const char*    name,
                      int32_t        number_of_threads,
                      ThreadPriority priority   = ThreadPriority::Normal,
                      int32_t        stack_size = DEFAULT_THREAD_STACK_SIZE);

    virtual ~ThreadWorkerGroup();

    int32_t GetNumberOfThreads() const {
        return thread_list.Num();
    }

    ThreadType& GetThread(int32_t index) {
        return *thread_list[index];
    }

    void SignalWorkAndWait();

  private:
    idList<ThreadType*, TAG_THREAD> thread_list;
    bool                            can_run_inline;
    bool                            is_single_thread;
};

template <class ThreadType>
inline ThreadWorkerGroup<ThreadType>::ThreadWorkerGroup(const char* name, int32_t number_of_threads, ThreadPriority priority, int32_t stack_size) {
    can_run_inline    = (number_of_threads < 0);
    is_single_thread  = false;
    number_of_threads = abs(number_of_threads);
    for (int32_t index = 0; index < number_of_threads; index++) {
        ThreadType* thread = new (TAG_THREAD) ThreadType;

        // thread->StartWorkerThread(va("%s_worker%index", name, index), priority, stack_size);
        thread->StartWorkerThread("worker", priority, stack_size);

        thread_list.Append(thread);
    }
}

template <class ThreadType>
inline ThreadWorkerGroup<ThreadType>::~ThreadWorkerGroup() {
    thread_list.DeleteContents();
}

template <class ThreadType>
inline void ThreadWorkerGroup<ThreadType>::SignalWorkAndWait() {
    if (is_single_thread) {
        for (int32_t index = 0; index < thread_list.Num(); index++) {
            thread_list[index]->Run();
        }
        return;
    }

    for (int32_t index = 0; index < thread_list.Num() - can_run_inline; index++) {
        thread_list[index]->SignalWork();
    }

    if (can_run_inline) {
        thread_list[thread_list.Num() - 1]->Run();
    }

    for (int32_t index = 0; index < thread_list.Num() - can_run_inline; index++) {
        thread_list[index]->WaitForThread();
    }
}

class ThreadSynchronizer {
  public:
    static const int32_t WAIT_INFINITE = -1;

    void SetNumberOfThreads(uint32_t count);
    void SignalOne(uint32_t thread_number);
    bool Synchronize(uint32_t thread_number, int32_t timeout = WAIT_INFINITE);

  private:
    idList<Signal*, TAG_THREAD> signals;
    InterlockedInteger          busy_count;
};

inline void ThreadSynchronizer::SetNumberOfThreads(uint32_t count) {
    assert(busy_count.GetValue() == signals.Num());

    if ((int32_t)count != signals.Num()) {
        signals.DeleteContents();
        signals.SetNum((int32_t)count);
        for (uint32_t index = 0; index < count; index++) {
            signals[index] = new Signal();
        }

        busy_count.SetValue(count);
        SYS_MEMORYBARRIER;
    }
}

inline void ThreadSynchronizer::SignalOne(uint32_t thread_number) {
    if (busy_count.Decrement() == 0) {
        busy_count.SetValue((uint32_t)signals.Num());
        SYS_MEMORYBARRIER;
        for (int32_t index = 0; index < signals.Num(); index++) {
            signals[index]->Raise();
        }
    }
}

inline bool ThreadSynchronizer::Synchronize(uint32_t thread_number, int32_t timeout) {
    return signals[thread_number]->Wait(timeout);
}
