#include "common/com_public.h"

#include "client/cl_public.h"
#include "client/cl_local.h"

#include "video_common/vid_public.h"

void Client_Start() {
    Video_Start();
}

void Client_Stop() {
    Video_Stop();
}

void Client_Frame() {
    Video_Frame();
}
