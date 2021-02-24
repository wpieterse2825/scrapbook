#include "common/com_public.h"

int main(int argument_count, char** arguments) {
    System_Start();

    while (true) {
        System_Frame();
    }

    System_Stop();
    return 0;
}
