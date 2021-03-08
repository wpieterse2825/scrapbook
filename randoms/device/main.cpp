#include <thread>
#include <iostream>

size_t ge_read         = 0;
size_t ge_write        = 0;
char   ge_buffer[2048] = {0};

void GraphicsEngineThread() {
    bool running = true;

    std::cout << "Graphics Engine Thread" << std::endl;

    while (running == true) {
        size_t current_read  = ge_read;
        size_t current_write = ge_write;
        size_t difference    = current_write - current_read;

        if (difference == 0) {
            std::this_thread::yield();
        } else {
            char command = ge_buffer[current_read + 0];
            char value   = ge_buffer[current_read + 1];

            switch (command) {
                case 0:
                    std::cout << "GET : Clear Color : " << int32_t {value} << std::endl;
                    break;
                case 1:
                    std::cout << "GET : Clear Depth : " << int32_t {value} << std::endl;
                    break;
                case 2:
                    std::cout << "GET : Clear Stencil : " << int32_t {value} << std::endl;
                    break;
                case 64:
                    std::cout << "GET : Quit" << std::endl;
                    running = false;
                    break;
                default:
                    std::cout << "GET : Unknown Command : " << int32_t {command} << std::endl;
                    break;
            }

            ge_read += 2;
        }
    }
}

int main() {
    std::thread graphics_engine_thread {GraphicsEngineThread};

    for (auto index = 0; index < 3 * 64; index++) {
        ge_buffer[ge_write + 0] = index % 3;
        ge_buffer[ge_write + 1] = index & 0xFF;
        ge_write += 2;
    }

    ge_buffer[ge_write + 0] = 64;
    ge_buffer[ge_write + 1] = 0;
    ge_write += 2;

    graphics_engine_thread.join();
    return 0;
}
