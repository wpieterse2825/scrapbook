// SPDX-License-Identifier: GPL-3.0

#include "formats/id_tech_0/wad/internal/builder_archive.hpp"

#include "g3log/g3log.hpp"

// TODO(wpieterse): Refactor Reset and Destruction code to share common functionality.
namespace wpieterse2825::game_tools::formats::id_tech_0::wad::internal {
    FBuilderArchiveInternal::FBuilderArchiveInternal(FAllocator* allocator)
      : _allocator {allocator}
      , _header {}
      , _entries {nullptr}
      , _data {nullptr}
      , _data_offset {0}
      , _file_offset {sizeof(FHeader)} {
        CHECK(allocator != nullptr) << "Allocator cannot be null.";

        _entries = _allocator->AllocateContainer<FEntry>(SMaximumEntryCount);
        _data    = _allocator->AllocateContainer<uint8_t>(SMaximumFileSize);
    }

    FBuilderArchiveInternal::~FBuilderArchiveInternal() {
        _file_offset = 0;
        _data_offset = 0;

        if (_data != nullptr) {
            _allocator->DeallocateContainer<uint8_t>(_data, SMaximumFileSize);
            _data = nullptr;
        }

        if (_entries != nullptr) {
            _allocator->DeallocateContainer<FEntry>(_entries, SMaximumEntryCount);
            _entries = nullptr;
        }

        _header    = FHeader {};
        _allocator = nullptr;
    }

    void FBuilderArchiveInternal::Signature(ESignature signature) {
        _header.signature = signature;
    }

    void FBuilderArchiveInternal::Entry(uint64_t name, FArchiveReader& archive) {
        auto entry = &_entries[_header.file_table_entries];
        _header.file_table_entries++;

        auto archive_size = archive.Size();
        entry->offset     = _file_offset;
        entry->size       = archive_size;
        entry->name       = name;

        auto data_pointer = _data + _data_offset;
        archive.Serialize(data_pointer, archive_size);

        _data_offset += archive_size;
        _file_offset += archive_size;
        _header.file_table_offset = _file_offset;
    }

    size_t FBuilderArchiveInternal::GetSize() {
        auto final_size = size_t {0};

        final_size += sizeof(FHeader);
        final_size += _data_offset;
        final_size += _header.file_table_entries * sizeof(FEntry);

        return final_size;
    }

    void FBuilderArchiveInternal::Finalize(FArchiveWriter& archive) {
        archive& _header;

        archive.Serialize(_data, _data_offset);

        for (auto entry_index = uint32_t {0}; entry_index < _header.file_table_entries; entry_index++) {
            archive& _entries[entry_index];
        }

        Reset();
    }

    void FBuilderArchiveInternal::Reset() {
        if (_data != nullptr) {
            _allocator->DeallocateContainer<uint8_t>(_data, SMaximumFileSize);
            _data = nullptr;
        }

        if (_entries != nullptr) {
            _allocator->DeallocateContainer<FEntry>(_entries, SMaximumEntryCount);
            _entries = nullptr;
        }

        _header  = FHeader {};
        _entries = _allocator->AllocateContainer<FEntry>(SMaximumEntryCount);
        _data    = _allocator->AllocateContainer<uint8_t>(SMaximumFileSize);

        _data_offset = 0;
        _file_offset = sizeof(FHeader);
    }
} // namespace wpieterse2825::game_tools::formats::id_tech_0::wad::internal
