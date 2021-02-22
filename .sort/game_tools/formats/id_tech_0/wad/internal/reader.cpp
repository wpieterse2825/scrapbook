// SPDX-License-Identifier: GPL-3.0

#include "formats/id_tech_0/wad/internal/reader.hpp"

#include "g3log/g3log.hpp"

namespace wpieterse2825::game_tools::formats::id_tech_0::wad::internal {
    FReaderInternal::FReaderInternal(FAllocator* allocator, FArchiveReader& archive)
      : _allocator {allocator}
      , _header {}
      , _entries {nullptr}
      , _data {nullptr}
      , _data_size {0} {
        CHECK(allocator != nullptr) << "Allocator cannot be null.";

        archive.Seek(0);
        archive& _header;

        auto entry_offset = _header.file_table_offset;
        auto entry_count  = _header.file_table_entries;

        archive.Seek(entry_offset);
        _entries = _allocator->AllocateContainer<FEntry>(entry_count);
        for (auto entry_index = uint32_t {0}; entry_index < entry_count; entry_index++) {
            auto& current_entry = _entries[entry_index];

            archive& current_entry;

            _data_size += current_entry.size;
        }

        archive.Seek(sizeof(FHeader));
        _data = _allocator->AllocateContainer<uint8_t>(_data_size);
        archive.Serialize(_data, _data_size);
    }

    FReaderInternal::~FReaderInternal() {
        if (_data != nullptr) {
            _allocator->DeallocateContainer<uint8_t>(_data, _data_size);
            _data = nullptr;
        }

        if (_entries != nullptr) {
            _allocator->DeallocateContainer<FEntry>(_entries, _header.file_table_entries);
            _entries = nullptr;
        }

        _data_size = 0;
        _header    = FHeader {};
        _allocator = nullptr;
    }

    ESignature FReaderInternal::Signature() {
        return _header.signature;
    }

    uint32_t FReaderInternal::EntryCount() {
        return _header.file_table_entries;
    }

    uint32_t FReaderInternal::IndexForName(uint64_t name) {
        auto entry_count = EntryCount();

        for (auto entry_index = uint32_t {0}; entry_index < entry_count; entry_index++) {
            auto& current_entry = _entries[entry_index];

            if (current_entry.name == name) {
                return entry_index;
            }
        }

        return SInvalidEntry;
    }

    uint32_t FReaderInternal::IndexForNameAfter(uint64_t name, uint64_t start_name) {
        auto entry_count = EntryCount();
        auto start_index = IndexForName(start_name);

        if (start_index == SInvalidEntry) {
            return SInvalidEntry;
        }

        for (auto entry_index = start_index; entry_index < entry_count; entry_index++) {
            auto& current_entry = _entries[entry_index];

            if (current_entry.name == name) {
                return entry_index;
            }
        }

        return SInvalidEntry;
    }

    uint32_t FReaderInternal::IndexForNameBetween(uint64_t name, uint64_t prefix_name, uint64_t postfix_name) {
        auto prefix_index = IndexForName(prefix_name);
        if (prefix_index == SInvalidEntry) {
            return SInvalidEntry;
        }

        auto postfix_index = IndexForName(postfix_name);
        if (postfix_index == SInvalidEntry) {
            return SInvalidEntry;
        }

        // Skip over prefix entry.
        prefix_index++;

        for (auto entry_index = prefix_index; entry_index < postfix_index; entry_index++) {
            auto& current_entry = _entries[entry_index];

            if (current_entry.name == name) {
                return entry_index;
            }
        }

        return SInvalidEntry;
    }

    uint64_t FReaderInternal::IndexName(uint32_t index) {
        CHECK(index < EntryCount()) << "Index is out of bounds.";

        return _entries[index].name;
    }

    uint32_t FReaderInternal::IndexSize(uint32_t index) {
        CHECK(index < EntryCount()) << "Index is out of bounds.";

        return _entries[index].size;
    }

    FMemoryArchiveReader FReaderInternal::IndexArchive(uint32_t index) {
        CHECK(index < EntryCount()) << "Index is out of bounds.";

        auto entry        = _entries[index];
        auto entry_buffer = _data + entry.offset;
        auto entry_size   = entry.size;

        return FMemoryArchiveReader {entry_buffer, entry_size};
    }
} // namespace wpieterse2825::game_tools::formats::id_tech_0::wad::internal
