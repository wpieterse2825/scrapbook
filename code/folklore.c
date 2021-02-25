#include "common/com_public.h"

int main(int argument_count, char** arguments) {
    Common_Start();

    while (true) {
        Common_Frame();
    }

    Common_Stop();
    return 0;
}
