// SPDX-License-Identifier: GPL-3.0

#pragma once

#include <stddef.h>
#include <stdint.h>

#include "foundation/virtual_base.hpp"

namespace wpieterse2825::game_tools {
    class FArchive : public FVirtualBase {
      public:
        FArchive();

        virtual size_t Size()                = 0;
        virtual size_t Tell()                = 0;
        virtual void   Seek(size_t location) = 0;

        virtual void Serialize(void* buffer, size_t buffer_size) = 0;

        bool IsRead();
        bool IsWrite();

      protected:
        bool _is_read;
        bool _is_write;
    };

    static inline FArchive& operator&(FArchive& archive, uint32_t& value) {
        archive.Serialize(&value, sizeof(value));

        return archive;
    }

    static inline FArchive& operator&(FArchive& archive, uint64_t& value) {
        archive.Serialize(&value, sizeof(value));

        return archive;
    }
} // namespace wpieterse2825::game_tools
