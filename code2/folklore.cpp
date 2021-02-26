#include "foundation/stack_record.hpp"

#include "framework/common.hpp"

int main(int argument_count, char** arguments) {
    GENERATE_STACK_RECORD();

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
