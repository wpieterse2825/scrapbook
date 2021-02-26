#include "framework/common.hpp"

int main(int argument_count, char** arguments) {
    common->Start();

    while (true) {
        auto is_quitting = common->Frame();
        if (is_quitting) {
            break;
        }
    }

    common->Stop();
    return 0;
}
