// SPDX-License-Identifier: GPL-3.0

#pragma once

#include <stddef.h>
#include <stdint.h>

#include "foundation/allocator.hpp"
#include "foundation/archive_reader.hpp"
#include "foundation/archive_writer.hpp"

#include "formats/id_tech_0/wad/signature.hpp"
#include "formats/id_tech_0/wad/builder_archive.hpp"

#include "formats/id_tech_0/wad/internal/header.hpp"
#include "formats/id_tech_0/wad/internal/entry.hpp"

namespace wpieterse2825::game_tools::formats::id_tech_0::wad::internal {
    class FBuilderArchiveInternal : public FBuilderArchive {
      public:
        FBuilderArchiveInternal(FAllocator* allocator);
        virtual ~FBuilderArchiveInternal();

        virtual void Signature(ESignature signature) override;
        virtual void Entry(uint64_t name, FArchiveReader& archive) override;

        virtual size_t GetSize() override;

        virtual void Finalize(FArchiveWriter& archive) override;
        virtual void Reset() override;

      private:
        FAllocator* _allocator;

        FHeader  _header;
        FEntry*  _entries;
        uint8_t* _data;

        size_t _data_offset;
        size_t _file_offset;
    };
} // namespace wpieterse2825::game_tools::formats::id_tech_0::wad::internal
