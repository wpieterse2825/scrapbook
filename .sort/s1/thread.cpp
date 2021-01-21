#include "stuff/thread.hpp"

#include <sched.h>
#include <errno.h>

typedef void* (*pthread_function_t)(void*);

#ifdef DEBUG_THREADS
static int32_t Sys_SetThreadName(pthread_t thread_handle, const char* name) {
    assert(strlen(name) < 16);

    int32_t ret = pthread_setname_np(thread_handle, name);
    if (ret != 0) {
        idLib::common->Printf("Setting threadname \"%s\" failed, reason: %s (%i)\n", name, strerror(errno), errno);
    }

    return ret;
}

static int32_t Sys_GetThreadName(pthread_t thread_handle, char* name_buffer, size_t name_buffer_length) {
    int32_t ret = pthread_getname_np(thread_handle, name_buffer, name_buffer_length);
    if (ret != 0) {
        idLib::common->Printf("Getting threadname failed, reason: %s (%i)\n", strerror(errno), errno);
    }

    return ret;
}

#endif // DEBUG_THREADS

uintptr_t Sys_CreateThread(
  ThreadCallbackFunction user_function, void* user_parameter, ThreadPriority priority, const char* name, int32_t stack_size, bool start_suspended) {
    pthread_attr_t thread_attributes;

    pthread_attr_init(&thread_attributes);
    if (pthread_attr_setdetachstate(&thread_attributes, PTHREAD_CREATE_JOINABLE) != 0) {
        printf("ERROR: pthread_attr_setdetachstate %s failed\n", name);
        return (uintptr_t)0;
    }

    pthread_t thread_handle;
    if (pthread_create((pthread_t*)&thread_handle, &thread_attributes, (pthread_function_t)user_function, user_parameter) != 0) {
        printf("ERROR: pthread_create %s failed\n", name);
        return (uintptr_t)0;
    }

#if defined(DEBUG_THREADS)
    if (Sys_SetThreadName(thread_handle, name) != 0) {
        printf("Warning: pthread_setname_np %s failed\n", name);
        return (uintptr_t)0;
    }
#endif

    pthread_attr_destroy(&thread_attributes);
    return (uintptr_t)thread_handle;
}

uintptr_t Sys_GetCurrentThreadID() {
    return (uintptr_t)pthread_self();
}

void Sys_DestroyThread(uintptr_t thread_handle) {
    char name[128] = {0};

    if (thread_handle == 0) {
        return;
    }

#if defined(DEBUG_THREADS)
    Sys_GetThreadName((pthread_t)thread_handle, name, sizeof(name));
#endif

    if (pthread_join((pthread_t)thread_handle, NULL) != 0) {
        printf("ERROR: pthread_join %s failed\n", name);
    }
}

void Sys_Yield() {
    pthread_yield();
}

void Sys_SignalCreate(SignalHandle& thread_handle, bool is_manual_reset) {
    thread_handle.is_manual_reset = is_manual_reset;
    thread_handle.signaled        = false;
    thread_handle.waiting         = 0;

    pthread_mutex_init(&thread_handle.mutex, NULL);
    pthread_cond_init(&thread_handle.cond, NULL);
}

void Sys_SignalDestroy(SignalHandle& thread_handle) {
    thread_handle.signaled = false;
    thread_handle.waiting  = 0;

    pthread_mutex_destroy(&thread_handle.mutex);
    pthread_cond_destroy(&thread_handle.cond);
}

void Sys_SignalRaise(SignalHandle& thread_handle) {
    pthread_mutex_lock(&thread_handle.mutex);

    if (thread_handle.is_manual_reset) {
        thread_handle.signaled = true;

        pthread_cond_broadcast(&thread_handle.cond);
    } else {
        if (thread_handle.waiting > 0) {
            pthread_cond_signal(&thread_handle.cond);
        } else {
            thread_handle.signaled = true;
        }
    }

    pthread_mutex_unlock(&thread_handle.mutex);
}

void Sys_SignalClear(SignalHandle& thread_handle) {
    pthread_mutex_lock(&thread_handle.mutex);

    thread_handle.signaled = false;
    pthread_mutex_unlock(&thread_handle.mutex);
}

bool Sys_SignalWait(SignalHandle& thread_handle, int32_t timeout) {
    int32_t status = 0;

    pthread_mutex_lock(&thread_handle.mutex);
    if (thread_handle.signaled) {
        if (!thread_handle.is_manual_reset) {
            thread_handle.signaled = false;
        }

        status = 0;
    } else {
        ++thread_handle.waiting;
        if (timeout == Signal::WAIT_INFINITE) {
            status = pthread_cond_wait(&thread_handle.cond, &thread_handle.mutex);
        } else {
            timespec ts;

            clock_gettime(CLOCK_REALTIME, &ts);
            ts.tv_nsec += (timeout % 1000) * 1000000;
            ts.tv_sec += timeout / 1000;
            if (ts.tv_nsec >= 1000000000) {
                ts.tv_nsec -= 1000000000;
                ts.tv_sec += 1;
            }

            status = pthread_cond_timedwait(&thread_handle.cond, &thread_handle.mutex, &ts);
        }

        --thread_handle.waiting;
    }

    pthread_mutex_unlock(&thread_handle.mutex);
    assert(status == 0 || (timeout != Signal::WAIT_INFINITE && status == ETIMEDOUT));
    return (status == 0);
}

void Sys_MutexCreate(MutexHandle& thread_handle) {
    pthread_mutexattr_t thread_attributes;

    pthread_mutexattr_init(&thread_attributes);
    pthread_mutexattr_settype(&thread_attributes, PTHREAD_MUTEX_ERRORCHECK);
    pthread_mutex_init(&thread_handle, &thread_attributes);
    pthread_mutexattr_destroy(&thread_attributes);
}

void Sys_MutexDestroy(MutexHandle& thread_handle) {
    pthread_mutex_destroy(&thread_handle);
}

bool Sys_MutexLock(MutexHandle& thread_handle, bool is_blocking) {
    if (pthread_mutex_trylock(&thread_handle) != 0) {
        if (!is_blocking) {
            return false;
        }

        pthread_mutex_lock(&thread_handle);
    }

    return true;
}

void Sys_MutexUnlock(MutexHandle& thread_handle) {
    pthread_mutex_unlock(&thread_handle);
}

InterlockedHandle Sys_InterlockedIncrement(InterlockedHandle& value) {
    return __sync_add_and_fetch(&value, 1);
}

InterlockedHandle Sys_InterlockedDecrement(InterlockedHandle& value) {
    return __sync_sub_and_fetch(&value, 1);
}

InterlockedHandle Sys_InterlockedAdd(InterlockedHandle& value, InterlockedHandle i) {
    return __sync_add_and_fetch(&value, i);
}

InterlockedHandle Sys_InterlockedSub(InterlockedHandle& value, InterlockedHandle i) {
    return __sync_sub_and_fetch(&value, i);
}

InterlockedHandle Sys_InterlockedExchange(InterlockedHandle& value, InterlockedHandle exchange) {
    return __sync_val_compare_and_swap(&value, value, exchange);
}

InterlockedHandle Sys_InterlockedCompareExchange(InterlockedHandle& value, InterlockedHandle comparand, InterlockedHandle exchange) {
    return __sync_val_compare_and_swap(&value, comparand, exchange);
}

void* Sys_InterlockedExchangePointer(void*& value, void* exchange) {
    return __sync_val_compare_and_swap(&value, value, exchange);
}

void* Sys_InterlockedCompareExchangePointer(void*& value, void* comparand, void* exchange) {
    return __sync_val_compare_and_swap(&value, comparand, exchange);
}

Thread::Thread()
  : thread_handle(0)
  , is_worker_thread(false)
  , is_running(false)
  , is_terminating(false)
  , has_more_work(false)
  , signal_work_done(true) {
}

Thread::~Thread() {
    StopThread(true);
    if (thread_handle) {
        Sys_DestroyThread(thread_handle);
    }
}

bool Thread::StartThread(const char* name_, ThreadPriority priority, int32_t stack_size) {
    if (is_running) {
        return false;
    }

    name           = name_;
    is_terminating = false;
    if (thread_handle) {
        Sys_DestroyThread(thread_handle);
    }

    thread_handle = Sys_CreateThread((ThreadCallbackFunction)SysstemThreadProcedure, this, priority, name, stack_size, false);
    is_running    = true;
    return true;
}

bool Thread::StartWorkerThread(const char* name_, ThreadPriority priority, int32_t stack_size) {
    if (is_running) {
        return false;
    }

    is_worker_thread = true;
    bool result      = StartThread(name_, priority, stack_size);
    signal_work_done.Wait(Signal::WAIT_INFINITE);
    return result;
}

void Thread::StopThread(bool wait) {
    if (!is_running) {
        return;
    }

    if (is_worker_thread) {
        signal_lock.Lock();

        has_more_work = true;
        signal_work_done.Clear();

        is_terminating = true;
        signal_has_more_work.Raise();

        signal_lock.Unlock();
    } else {
        is_terminating = true;
    }

    if (wait) {
        WaitForThread();
    }
}

void Thread::WaitForThread() {
    if (is_worker_thread) {
        signal_work_done.Wait(Signal::WAIT_INFINITE);
    } else if (is_running) {
        Sys_DestroyThread(thread_handle);
    }
}

void Thread::SignalWork() {
    if (is_worker_thread) {
        signal_lock.Lock();

        has_more_work = true;
        signal_work_done.Clear();
        signal_has_more_work.Raise();

        signal_lock.Unlock();
    }
}

bool Thread::IsWorkDone() {
    if (is_worker_thread) {
        if (signal_work_done.Wait(0)) {
            return true;
        }
    }

    return false;
}

int32_t Thread::SysstemThreadProcedure(Thread* thread) {
    int32_t return_value = 0;

    if (thread->is_worker_thread) {
        for (;;) {
            thread->signal_lock.Lock();
            if (thread->has_more_work) {
                thread->has_more_work = false;
                thread->signal_has_more_work.Clear();
                thread->signal_lock.Unlock();
            } else {
                thread->signal_work_done.Raise();
                thread->signal_lock.Unlock();
                thread->signal_has_more_work.Wait(Signal::WAIT_INFINITE);
                continue;
            }

            if (thread->is_terminating) {
                break;
            }

            return_value = thread->Run();
        }

        thread->signal_work_done.Raise();
    } else {
        return_value = thread->Run();
    }

    thread->is_running = false;
    return return_value;
}

int32_t Thread::Run() {
    return 0;
}
