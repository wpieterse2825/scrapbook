#include <SDL2/SDL.h>

#include "common/com_shared.h"
#include "common/com_public.h"

#include "client/cl_public.h"
#include "client/cl_local.h"

#include "video_common/vid_public.h"

void Client_Start(void) {
    Video_Start();
}

void Client_Stop(void) {
    Video_Stop();
}

void Client_Frame(void) {
    Video_BeginFrame();
    Video_EndFrame();
}
