#include <SDL2/SDL.h>

#include "common/com_public.h"
#include "common/com_local.h"

int main(int argument_count, char** arguments) {
    // TODO(wpieterse): Get a place for this.
    if (SDL_InitSubSystem(SDL_INIT_VIDEO) != 0) {
        Common_Error("Failed to initialize the SDL video subsystem : %s.", SDL_GetError());
    }

    ConsoleSystem_Start();
    Common_Start();

    while (true) {
        bool quit_requested = Common_Frame();
        if (quit_requested == true) {
            break;
        }
    }

    Common_Stop();
    ConsoleSystem_Stop();

    SDL_QuitSubSystem(SDL_INIT_VIDEO);
    SDL_Quit();
    return 0;
}
