#include <SDL2/SDL.h>

#include "common/com_shared.h"
#include "common/com_public.h"

int main(int argument_count, char** arguments) {
    // TODO(wpieterse): Get a place for this.
    if (SDL_InitSubSystem(SDL_INIT_VIDEO) != 0) {
        Common_Error("Failed to initialize the SDL video subsystem : %s.", SDL_GetError());
    }

    Common_Start();

    while (true) {
        if (Common_IsQuitting() == true) {
            break;
        }

        Common_Frame();
    }

    Common_Stop();

    SDL_QuitSubSystem(SDL_INIT_VIDEO);
    SDL_Quit();
    return 0;
}
