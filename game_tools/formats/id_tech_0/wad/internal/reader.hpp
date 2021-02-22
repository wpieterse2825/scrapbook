// SPDX-License-Identifier: GPL-3.0

#pragma once

#include <stddef.h>
#include <stdint.h>

#include "foundation/allocator.hpp"
#include "foundation/archive_reader.hpp"
#include "foundation/memory_archive_reader.hpp"

#include "formats/id_tech_0/wad/signature.hpp"
#include "formats/id_tech_0/wad/reader.hpp"

#include "formats/id_tech_0/wad/internal/header.hpp"
#include "formats/id_tech_0/wad/internal/entry.hpp"

namespace wpieterse2825::game_tools::formats::id_tech_0::wad::internal {
    class FReaderInternal : public FReader {
      public:
        FReaderInternal(FAllocator* allocator, FArchiveReader& archive);
        virtual ~FReaderInternal();

        virtual ESignature Signature() override;
        virtual uint32_t   EntryCount() override;

        virtual uint32_t IndexForName(uint64_t name) override;
        virtual uint32_t IndexForNameAfter(uint64_t name, uint64_t start_name) override;
        virtual uint32_t IndexForNameBetween(uint64_t name, uint64_t prefix_name, uint64_t postfix_name) override;

        virtual uint64_t             IndexName(uint32_t index) override;
        virtual uint32_t             IndexSize(uint32_t index) override;
        virtual FMemoryArchiveReader IndexArchive(uint32_t index) override;

      private:
        FAllocator* _allocator;

        FHeader  _header;
        FEntry*  _entries;
        uint8_t* _data;
        size_t   _data_size;
    };
} // namespace wpieterse2825::game_tools::formats::id_tech_0::wad::internal
