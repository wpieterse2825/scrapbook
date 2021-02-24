#include <stdarg.h>
#include <stdio.h>

#include <SDL2/SDL.h>

#include "common/com_public.h"

#include "server/sv_public.h"
#include "client/cl_public.h"

#include "common/allocator.h"
#include "common/jobs.h"

void System_Error(const char* message, ...) {
    char    formatted_message[16 * 1024] = {0};
    va_list argument_list                = {};

    System_Stop();

    va_start(argument_list, message);
    vsprintf(formatted_message, message, argument_list);
    va_end(argument_list);

    printf("ERROR : %s\n", formatted_message);
    exit(1);
}

void System_JobCallback(int range_start, int range_end, int thread_index, void* user) {
    printf(" * %d - %d\n", range_start, range_end);
}

void System_Start() {
    sx_alloc* allocator = sx_alloc_malloc();
    sx_job_context_desc context_desc = {
        .num_threads = 12,
        .max_fibers = 1024,
        .fiber_stack_sz = 1 * 1024 * 1024,
        .thread_init_cb = NULL,
        .thread_shutdown_cb = NULL,
        .thread_user_data = NULL,
    };

    sx_job_context* context = sx_job_create_context(allocator, &context_desc);

    sx_job_t job = sx_job_dispatch(context, 1024, System_JobCallback, NULL, SX_JOB_PRIORITY_NORMAL, 0);
    sx_job_wait_and_del(context, job);

    sx_job_destroy_context(context, allocator);

    Server_Start();
    Client_Start();
}

void System_Stop() {
    Client_Stop();
    Server_Stop();

    SDL_Quit();
}

void System_PumpEvents() {
    SDL_Event sdl_event = {};

    while (SDL_PollEvent(&sdl_event) == true) {
        if (sdl_event.type == SDL_QUIT) {
            System_Error("Quit.");
        } else if (sdl_event.type == SDL_KEYUP) {
            if (sdl_event.key.keysym.sym == SDLK_ESCAPE) {
                System_Error("Quit.");
            }
        }
    }
}

void System_Frame() {
    System_PumpEvents();

    Server_Frame();
    Client_Frame();
}
