// SPDX-License-Identifier: GPL-3.0

#include "g3log/g3log.hpp"

#include "foundation/utilities.hpp"

namespace wpieterse2825::game_tools {
    uint8_t* ReadCompleteFile(FAllocator* allocator, const char* filename, size_t* buffer_size) {
        auto file = fopen(filename, "rb");
        CHECK(file != nullptr) << "Failed to open " << filename << " for reading.";

        fseek(file, 0, SEEK_END);
        *buffer_size = static_cast<size_t>(ftell(file));
        fseek(file, 0, SEEK_SET);

        auto buffer = allocator->AllocateContainer<uint8_t>(*buffer_size);
        fread(buffer, *buffer_size, 1, file);
        fclose(file);

        return buffer;
    }
} // namespace wpieterse2825::game_tools
