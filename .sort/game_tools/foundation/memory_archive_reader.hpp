// SPDX-License-Identifier: GPL-3.0

#pragma once

#include <stddef.h>
#include <stdint.h>

#include "foundation/archive_reader.hpp"

namespace wpieterse2825::game_tools {
    class FMemoryArchiveReader : public FArchiveReader {
      public:
        FMemoryArchiveReader(const uint8_t* buffer, size_t buffer_size);

        virtual size_t Size() override;
        virtual size_t Tell() override;
        virtual void   Seek(size_t location) override;

        virtual void Serialize(void* buffer, size_t buffer_size) override;

      private:
        const uint8_t* _buffer;
        size_t         _buffer_size;
        size_t         _buffer_location;
    };
} // namespace wpieterse2825::game_tools
