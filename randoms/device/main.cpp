#include <thread>
#include <mutex>
#include <iostream>

#include "other.hpp"

constexpr size_t GraphicsEngineBufferSize = 16;

struct FRingBuffer {
    uint64_t* buffer;
    size_t    buffer_size;

    int64_t write_pointer;
    int64_t read_pointer;

    int64_t write_index;
    int64_t read_index;
};

void CreateRingBuffer(FRingBuffer* ring_buffer, uint64_t* buffer, size_t buffer_size) {
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

void WriteRingBuffer(FRingBuffer* ring_buffer, uint64_t value) {
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

uint64_t ReadRingBuffer(FRingBuffer* ring_buffer) {
    const auto buffer_size  = ring_buffer->buffer_size;
    const auto read_pointer = ring_buffer->read_pointer;
    const auto read_index   = ring_buffer->read_index;
    const auto read_offset  = read_pointer + read_index;
    const auto read_wrapped = read_offset % buffer_size;

    ring_buffer->read_index++;

    return ring_buffer->buffer[read_wrapped];
}

uint64_t PeekRingBuffer(FRingBuffer* ring_buffer) {
    const auto buffer_size  = ring_buffer->buffer_size;
    const auto read_pointer = ring_buffer->read_pointer;
    const auto read_wrapped = read_pointer % buffer_size;

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

union FCommandHeader {
    uint64_t raw;

    BitField<0, 8, uint64_t> command;
    BitField<8, 8, uint64_t> parameters;
};

static_assert(sizeof(FCommandHeader) == sizeof(uint64_t));

union FClearColorTarget {
    uint64_t raw;

    BitField<0, 8, uint64_t>  target;
    BitField<8, 8, uint64_t>  red;
    BitField<16, 8, uint64_t> green;
    BitField<24, 8, uint64_t> blue;
    BitField<32, 8, uint64_t> alpha;
};

static_assert(sizeof(FClearColorTarget) == sizeof(uint64_t));

FRingBuffer graphics_engine_ring {};

FCommandHeader PeekGraphicsEngineCommandHeader(FRingBuffer* ring_buffer) {
    FCommandHeader header {};

    header.raw = PeekRingBuffer(ring_buffer);

    return header;
}

FCommandHeader ReadGraphicsEngineCommandHeader(FRingBuffer* ring_buffer) {
    FCommandHeader header {};

    header.raw = ReadRingBuffer(ring_buffer);

    return header;
}

void ProcessGraphicsEngineClearColorCommand(FRingBuffer* ring_buffer, FCommandHeader* command_header) {
    uint64_t parameters = command_header->parameters.Value();

    std::cout << "Clear Color :" << std::endl;

    for (uint64_t current_parameter = 0; current_parameter < parameters; current_parameter++) {
        FClearColorTarget target {};

        target.raw = ReadRingBuffer(ring_buffer);

        std::cout << " - Target " << target.target.Value() << std::endl;
        std::cout << "   o Red   : " << target.red.Value() << std::endl;
        std::cout << "   o Green : " << target.green.Value() << std::endl;
        std::cout << "   o Blue  : " << target.blue.Value() << std::endl;
        std::cout << "   o Alpha : " << target.alpha.Value() << std::endl;
    }
}

void ProcessGraphicsEngineClearDepthCommand(FRingBuffer* ring_buffer, FCommandHeader* command_header) {
    std::cout << "Clear Depth" << std::endl;
}

void ProcessGraphicsEngineClearStencilCommand(FRingBuffer* ring_buffer, FCommandHeader* command_header) {
    std::cout << "Clear Stencil" << std::endl;
}

void ProcessGraphicsEngineUnknownCommand(FRingBuffer* ring_buffer, FCommandHeader* command_header) {
    uint64_t command    = command_header->command.Value();
    uint64_t parameters = command_header->parameters.Value();

    std::cout << "Unknown Command : " << command << std::endl;

    for (uint64_t current_parameter = 0; current_parameter < parameters; current_parameter++) {
        ReadRingBuffer(ring_buffer);
    }
}

bool ProcessGraphicsEngineCommand(FRingBuffer* ring_buffer, FCommandHeader* command_header) {
    bool     result  = true;
    uint64_t command = command_header->command.Value();

    switch (command) {
        case 0:
            ProcessGraphicsEngineClearColorCommand(ring_buffer, command_header);
            break;
        case 1:
            ProcessGraphicsEngineClearDepthCommand(ring_buffer, command_header);
            break;
        case 2:
            ProcessGraphicsEngineClearStencilCommand(ring_buffer, command_header);
            break;
        case 64:
            std::cout << "Quit" << std::endl;
            result = false;
            break;
        default:
            ProcessGraphicsEngineUnknownCommand(ring_buffer, command_header);
            break;
    }

    return result;
}

void GraphicsEngineThread() {
    bool running = true;

    while (running == true) {
        int64_t read_available = ReadCountRingBuffer(&graphics_engine_ring);

        if (read_available < 1) {
            std::this_thread::yield();
        } else {
            FCommandHeader header = PeekGraphicsEngineCommandHeader(&graphics_engine_ring);
            if (read_available < (1 + header.parameters.Value())) {
                std::this_thread::yield();
            } else {
                BeginRingBufferRead(&graphics_engine_ring);

                header  = ReadGraphicsEngineCommandHeader(&graphics_engine_ring);
                running = ProcessGraphicsEngineCommand(&graphics_engine_ring, &header);

                EndRingBufferRead(&graphics_engine_ring);
            }
        }
    }
}

int main() {
    system("clear");

    uint64_t* ring_buffer = (uint64_t*)malloc(sizeof(uint64_t) * GraphicsEngineBufferSize);
    uint64_t  stalls      = 0;

    CreateRingBuffer(&graphics_engine_ring, ring_buffer, GraphicsEngineBufferSize);

    std::thread graphics_engine_thread {GraphicsEngineThread};

    for (auto index = 0; index < 3 * 32; index++) {
        while (true) {
            int64_t write_available = WriteCountRingBuffer(&graphics_engine_ring);
            if (write_available >= 3) {
                break;
            } else {
                std::this_thread::yield();
            }
        }

        BeginRingBufferWrite(&graphics_engine_ring);

        FCommandHeader header {};

        uint64_t command_index = index % 3;

        header.raw = 0;
        header.command.Assign(command_index);

        if (command_index == 0) {
            header.parameters.Assign(2);
        }

        WriteRingBuffer(&graphics_engine_ring, header.raw);

        if (command_index == 0) {
            FClearColorTarget clear_1 {};

            clear_1.target.Assign(0);
            clear_1.red.Assign(255);
            clear_1.green.Assign(128);
            clear_1.blue.Assign(0);
            clear_1.alpha.Assign(255);

            WriteRingBuffer(&graphics_engine_ring, clear_1.raw);

            FClearColorTarget clear_2 {};

            clear_2.target.Assign(1);
            clear_2.red.Assign(0);
            clear_2.green.Assign(128);
            clear_2.blue.Assign(255);
            clear_2.alpha.Assign(128);

            WriteRingBuffer(&graphics_engine_ring, clear_2.raw);
        }

        EndRingBufferWrite(&graphics_engine_ring);
    }

    BeginRingBufferWrite(&graphics_engine_ring);
    WriteRingBuffer(&graphics_engine_ring, 64);
    EndRingBufferWrite(&graphics_engine_ring);

    graphics_engine_thread.join();

    DestroyRingBuffer(&graphics_engine_ring);

    free(ring_buffer);

    return 0;
}
