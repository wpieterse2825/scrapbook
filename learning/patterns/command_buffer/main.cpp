#include <stdint.h>
#include <memory.h>
#include <iostream>

struct CommandBuffer {
    uint8_t* allocation;
    size_t   size;
    size_t   used;
};

void CreateCommandBuffer(CommandBuffer& command_buffer, size_t size) {
    command_buffer.allocation = reinterpret_cast<uint8_t*>(malloc(size));
    command_buffer.size       = size;
    command_buffer.used       = 0;
}

void DestroyCommandBuffer(CommandBuffer& command_buffer) {
    free(command_buffer.allocation);

    command_buffer.allocation = nullptr;
    command_buffer.size       = 0;
    command_buffer.used       = 0;
}

template <typename ResultType>
ResultType* AllocateCommand(CommandBuffer& command_buffer) {
    auto allocation_size = sizeof(ResultType);
    auto allocation      = command_buffer.allocation + command_buffer.used;

    command_buffer.used += allocation_size;

    return reinterpret_cast<ResultType*>(allocation);
}

enum class CommandType : uint8_t {
    Unknown = 0,
    Read    = 1,
    Write   = 2,
};

struct Command {
    CommandType type;
};

struct ReadCommand {
    Command  command;
    uint16_t offset;
    uint16_t length;
};

struct WriteCommand {
    Command  command;
    uint16_t offset;
    uint16_t length;
};

ReadCommand* AllocateReadCommand(CommandBuffer& command_buffer, uint16_t offset, uint16_t length) {
    auto result = AllocateCommand<ReadCommand>(command_buffer);

    result->command.type = CommandType::Read;
    result->offset       = offset;
    result->length       = length;

    return result;
}

WriteCommand* AllocateWriteCommand(CommandBuffer& command_buffer, uint16_t offset, uint16_t length) {
    auto result = AllocateCommand<WriteCommand>(command_buffer);

    result->command.type = CommandType::Write;
    result->offset       = offset;
    result->length       = length;

    return result;
}

void ProcessReadCommand(ReadCommand* command) {
    std::cout << " - Read Command (" << reinterpret_cast<void*>(command) << "):" << std::endl;
    std::cout << "   - Offset : " << command->offset << std::endl;
    std::cout << "   - Length : " << command->length << std::endl;
}

void ProcessWriteCommand(WriteCommand* command) {
    std::cout << " - Write Command (" << reinterpret_cast<void*>(command) << "):" << std::endl;
    std::cout << "   - Offset : " << command->offset << std::endl;
    std::cout << "   - Length : " << command->length << std::endl;
}

void Process(CommandBuffer& command_buffer) {
    auto process_offset = 0;
    auto process_left   = command_buffer.used;

    while (process_left > 0) {
        auto command = reinterpret_cast<Command*>(command_buffer.allocation + process_offset);
        if (command->type == CommandType::Read) {
            ProcessReadCommand(reinterpret_cast<ReadCommand*>(command));

            process_offset += sizeof(ReadCommand);
            process_left -= sizeof(ReadCommand);
        } else if (command->type == CommandType::Write) {
            ProcessWriteCommand(reinterpret_cast<WriteCommand*>(command));

            process_offset += sizeof(WriteCommand);
            process_left -= sizeof(WriteCommand);
        } else {
            std::cout << "Error" << std::endl;
            break;
        }
    }

    command_buffer.used = 0;
}

int main() {
    CommandBuffer command_buffer{};
    
    std::cout << "==================================================" << std::endl;
    std::cout << "Command Buffer:" << std::endl;

    CreateCommandBuffer(command_buffer, 1024);

    std::cout << " - Command buffer base : " << reinterpret_cast<void*>(command_buffer.allocation) << std::endl;
    std::cout << std::endl;

    AllocateWriteCommand(command_buffer, 20, 200);
    AllocateReadCommand(command_buffer, 21, 22);
    AllocateReadCommand(command_buffer, 40, 22);

    Process(command_buffer);

    DestroyCommandBuffer(command_buffer);

    std::cout << "==================================================" << std::endl;

    return 0;
}
