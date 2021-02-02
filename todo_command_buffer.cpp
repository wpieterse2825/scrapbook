#include <memory.h>
#include <iostream>

struct CommandBuffer {
    uint8_t* buffer;
    size_t   buffer_length;
    size_t   buffer_offset;
};

CommandBuffer Create(size_t length) {
    CommandBuffer result;

    result.buffer        = (uint8_t*)malloc(length);
    result.buffer_length = length;
    result.buffer_offset = 0;

    return result;
}

void Destroy(CommandBuffer* buffer) {
    free(buffer->buffer);

    buffer->buffer        = nullptr;
    buffer->buffer_length = 0;
    buffer->buffer_offset = 0;
}

void* Allocate(CommandBuffer* buffer, size_t length) {
    void* result = buffer->buffer + buffer->buffer_offset;

    buffer->buffer_offset += length;
    return result;
}

#define UNKNOWN_COMMAND 0
#define READ_COMMAND    1
#define WRITE_COMMAND   2

struct Command {
    uint8_t command;
};

struct ReadCommand {
    uint8_t  command;
    uint16_t offset;
    uint16_t length;
};

struct WriteCommand {
    uint8_t  command;
    uint16_t offset;
    uint16_t length;
};

ReadCommand* AllocateReadCommand(CommandBuffer* buffer, uint16_t offset, uint16_t length) {
    ReadCommand* result = (ReadCommand*)Allocate(buffer, sizeof(ReadCommand));

    result->command     = READ_COMMAND;
    result->offset      = offset;
    result->length      = length;

    return result;
}

WriteCommand* AllocateWriteCommand(CommandBuffer* buffer, uint16_t offset, uint16_t length) {
    WriteCommand* result = (WriteCommand*)Allocate(buffer, sizeof(WriteCommand));

    result->command     = WRITE_COMMAND;
    result->offset      = offset;
    result->length      = length;

    return result;
}

void Process(CommandBuffer* buffer) {
    size_t process_offset = 0;
    size_t process_left   = buffer->buffer_offset;

    while (process_left > 0) {
        Command* command = (Command*)(buffer->buffer + process_offset);
        if (command->command == READ_COMMAND) {
            ReadCommand* read_command = (ReadCommand*)command;
            process_offset += sizeof(ReadCommand);
            process_left -= sizeof(ReadCommand);

            std::cout << "READ  : " << read_command->length << " - " << read_command->offset << std::endl;
        } else if (command->command == WRITE_COMMAND) {
            WriteCommand* write_command = (WriteCommand*)command;
            process_offset += sizeof(WriteCommand);
            process_left -= sizeof(WriteCommand);

            std::cout << "WRITE : " << write_command->length << " - " << write_command->offset << std::endl;
        } else {
            std::cout << "ERROR" << std::endl;
            break;
        }
    }

    buffer->buffer_offset = 0;
}

int main() {
    CommandBuffer buffer = Create(1024);

    AllocateWriteCommand(&buffer, 20, 200);
    AllocateReadCommand(&buffer, 21, 22);
    AllocateReadCommand(&buffer, 40, 22);

    Process(&buffer);

    Destroy(&buffer);
    return 0;
}
