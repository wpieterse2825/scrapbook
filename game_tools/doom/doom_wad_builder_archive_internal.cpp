#include <assert.h>

#include "game_tools/doom/doom_wad_builder_archive_internal.hpp"

namespace wpieterse2825::scrapbook::game_tools::doom {
    DoomWadBuilderArchiveInternal::DoomWadBuilderArchiveInternal(Allocator* allocator)
      : _allocator {allocator}
      , _header {}
      , _entries {nullptr}
      , _data {nullptr}
      , _data_offset {0}
      , _file_offset {sizeof(DoomWadHeader)} {
        assert(allocator != nullptr);

        _entries = _allocator->AllocateContainer<DoomWadEntry>(DoomWadMaximumEntries);
        _data    = _allocator->AllocateContainer<uint8_t>(DoomWadMaximumSize);
    }

    DoomWadBuilderArchiveInternal::~DoomWadBuilderArchiveInternal() {
        _file_offset = 0;
        _data_offset = 0;

        if (_data != nullptr) {
            _allocator->DeallocateContainer<uint8_t>(_data, DoomWadMaximumSize);
            _data = nullptr;
        }

        if (_entries != nullptr) {
            _allocator->DeallocateContainer<DoomWadEntry>(_entries, DoomWadMaximumEntries);
            _entries = nullptr;
        }

        _header    = DoomWadHeader {};
        _allocator = nullptr;
    }

    void DoomWadBuilderArchiveInternal::Signature(DoomWadSignature signature) {
        _header.signature = signature;
    }

    void DoomWadBuilderArchiveInternal::Entry(uint64_t name, ArchiveReader& archive) {
        assert((_header.file_table_entries + 1) != DoomWadMaximumEntries);

        auto entry = &_entries[_header.file_table_entries];
        _header.file_table_entries++;

        auto archive_size = archive.Size();
        assert((_file_offset + archive_size) < DoomWadMaximumSize);

        entry->offset = _file_offset;
        entry->size   = archive_size;
        entry->name   = name;

        auto data_pointer = _data + _data_offset;
        archive.Serialize(data_pointer, archive_size);

        _data_offset += archive_size;
        _file_offset += archive_size;
        _header.file_table_offset = _file_offset;
    }

    size_t DoomWadBuilderArchiveInternal::GetSize() {
        auto final_size = size_t {0};

        final_size += sizeof(DoomWadHeader);
        final_size += _data_offset;
        final_size += _header.file_table_entries * sizeof(DoomWadEntry);

        return final_size;
    }

    void DoomWadBuilderArchiveInternal::Finalize(ArchiveWriter& archive) {
        archive& _header;

        archive.Serialize(_data, _data_offset);

        for (auto entry_index = uint32_t {0}; entry_index < _header.file_table_entries; entry_index++) {
            archive& _entries[entry_index];
        }

        Reset();
    }

    void DoomWadBuilderArchiveInternal::Reset() {
        if (_data != nullptr) {
            _allocator->DeallocateContainer<uint8_t>(_data, DoomWadMaximumSize);
            _data = nullptr;
        }

        if (_entries != nullptr) {
            _allocator->DeallocateContainer<DoomWadEntry>(_entries, DoomWadMaximumEntries);
            _entries = nullptr;
        }

        _header  = DoomWadHeader {};
        _entries = _allocator->AllocateContainer<DoomWadEntry>(DoomWadMaximumEntries);
        _data    = _allocator->AllocateContainer<uint8_t>(DoomWadMaximumSize);

        _data_offset = 0;
        _file_offset = sizeof(DoomWadHeader);
    }
} // namespace wpieterse2825::scrapbook::game_tools::doom
