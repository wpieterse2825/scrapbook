#include <thread>
#include <mutex>
#include <iostream>

constexpr size_t GraphicsEngineBufferSize = 128 + 1;

struct FRingBuffer {
    uint8_t* buffer;
    size_t   buffer_size;

    int64_t write_pointer;
    int64_t read_pointer;

    int64_t write_index;
    int64_t read_index;
};

void CreateRingBuffer(FRingBuffer* ring_buffer, uint8_t* buffer, size_t buffer_size) {
    ring_buffer->buffer        = buffer;
    ring_buffer->buffer_size   = buffer_size;
    ring_buffer->write_pointer = 0;
    ring_buffer->read_pointer  = 0;
    ring_buffer->write_index   = 0;
    ring_buffer->read_index    = 0;
}

void DestroyRingBuffer(FRingBuffer* ring_buffer) {
    ring_buffer->read_index    = 0;
    ring_buffer->write_index   = 0;
    ring_buffer->read_pointer  = 0;
    ring_buffer->write_pointer = 0;
    ring_buffer->buffer_size   = 0;
    ring_buffer->buffer        = nullptr;
}

void BeginRingBufferWrite(FRingBuffer* ring_buffer) {
}

void EndRingBufferWrite(FRingBuffer* ring_buffer) {
    ring_buffer->write_pointer += ring_buffer->write_index;

    ring_buffer->write_index = 0;
}

void WriteRingBuffer(FRingBuffer* ring_buffer, uint8_t value) {
    const auto buffer_size   = ring_buffer->buffer_size;
    const auto write_pointer = ring_buffer->write_pointer;
    const auto write_index   = ring_buffer->write_index;
    const auto write_offset  = write_pointer + write_index;
    const auto write_wrapped = write_offset % buffer_size;

    ring_buffer->write_index++;

    ring_buffer->buffer[write_wrapped] = value;
}

void BeginRingBufferRead(FRingBuffer* ring_buffer) {
}

void EndRingBufferRead(FRingBuffer* ring_buffer) {
    ring_buffer->read_pointer += ring_buffer->read_index;

    ring_buffer->read_index = 0;
}

uint8_t ReadRingBuffer(FRingBuffer* ring_buffer) {
    const auto buffer_size  = ring_buffer->buffer_size;
    const auto read_pointer = ring_buffer->read_pointer;
    const auto read_index   = ring_buffer->read_index;
    const auto read_offset  = read_pointer + read_index;
    const auto read_wrapped = read_offset % buffer_size;

    ring_buffer->read_index++;

    return ring_buffer->buffer[read_wrapped];
}

int64_t ReadCountRingBuffer(FRingBuffer* ring_buffer) {
    const auto buffer_size   = ring_buffer->buffer_size;
    const auto write_pointer = ring_buffer->write_pointer;
    const auto read_pointer  = ring_buffer->read_pointer;

    if (read_pointer <= write_pointer) {
        return write_pointer - read_pointer;
    }

    return buffer_size - read_pointer + write_pointer;
}

int64_t WriteCountRingBuffer(FRingBuffer* ring_buffer) {
    const auto buffer_size   = ring_buffer->buffer_size;
    const auto write_pointer = ring_buffer->write_pointer;
    const auto read_pointer  = ring_buffer->read_pointer;

    if (read_pointer <= write_pointer) {
        return buffer_size - (write_pointer - read_pointer) - 1;
    }

    return (read_pointer - write_pointer) - 1;
}

std::mutex print_mutex;

FRingBuffer graphics_engine_ring {};

void GraphicsEngineThread() {
    bool running = true;

    {
        std::lock_guard<std::mutex> lock {print_mutex};
        std::cout << "Graphics Engine Thread" << std::endl;
    }

    while (running == true) {
        int64_t difference = ReadCountRingBuffer(&graphics_engine_ring);

        if (difference < 2) {
            std::this_thread::yield();
        } else {
            BeginRingBufferRead(&graphics_engine_ring);

            uint8_t command = ReadRingBuffer(&graphics_engine_ring);
            uint8_t value   = ReadRingBuffer(&graphics_engine_ring);

            EndRingBufferRead(&graphics_engine_ring);

            switch (command) {
                case 0:
                    {
                        std::lock_guard<std::mutex> lock {print_mutex};
                        std::cout << "GET : Clear Color : " << int32_t {value} << std::endl;
                    }
                    break;
                case 1:
                    {
                        std::lock_guard<std::mutex> lock {print_mutex};
                        std::cout << "GET : Clear Depth : " << int32_t {value} << std::endl;
                    }
                    break;
                case 2:
                    {
                        std::lock_guard<std::mutex> lock {print_mutex};
                        std::cout << "GET : Clear Stencil : " << int32_t {value} << std::endl;
                    }
                    break;
                case 64:
                    {
                        std::lock_guard<std::mutex> lock {print_mutex};
                        std::cout << "GET : Quit" << std::endl;
                    }
                    running = false;
                    break;
                default:
                    {
                        std::lock_guard<std::mutex> lock {print_mutex};
                        std::cout << "GET : Unknown Command : " << int32_t {command} << std::endl;
                    }
                    break;
            }
        }
    }
}

int main() {
    system("clear");

    uint8_t* ring_buffer = (uint8_t*)malloc(sizeof(uint8_t) * GraphicsEngineBufferSize);

    CreateRingBuffer(&graphics_engine_ring, ring_buffer, GraphicsEngineBufferSize);

    std::thread graphics_engine_thread {GraphicsEngineThread};

    for (auto index = 0; index < 3 * 64; index++) {
        while (true) {
            int64_t write_available = WriteCountRingBuffer(&graphics_engine_ring);
            if (write_available >= 2) {
                break;
            } else {
                std::lock_guard<std::mutex> lock {print_mutex};
                std::cout << "PIPELINE STALL" << std::endl;
            }
        }

        BeginRingBufferWrite(&graphics_engine_ring);

        WriteRingBuffer(&graphics_engine_ring, index % 3);
        WriteRingBuffer(&graphics_engine_ring, index & 0xFF);

        EndRingBufferWrite(&graphics_engine_ring);
    }

    BeginRingBufferWrite(&graphics_engine_ring);

    WriteRingBuffer(&graphics_engine_ring, 64);
    WriteRingBuffer(&graphics_engine_ring, 0);

    EndRingBufferWrite(&graphics_engine_ring);

    graphics_engine_thread.join();

    DestroyRingBuffer(&graphics_engine_ring);

    free(ring_buffer);

    return 0;
}
