set(SOURCE_RANDOMS_PARALLEL_JOB_LIST
    list.hpp
    main.cpp
    parallel_job_list.cpp
    parallel_job_list.hpp
    shared.hpp
    thread.cpp
    thread.hpp
)

add_executable(randoms_parallel_job_list
    ${SOURCE_RANDOMS_PARALLEL_JOB_LIST}
)

target_link_libraries(randoms_parallel_job_list
    ${CMAKE_THREAD_LIBS_INIT}
)
