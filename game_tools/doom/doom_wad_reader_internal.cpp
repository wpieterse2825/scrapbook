#include <assert.h>

#include "game_tools/doom/doom_wad_reader_internal.hpp"

namespace wpieterse2825::scrapbook::game_tools::doom {

    DoomWadReaderInternal::DoomWadReaderInternal(Allocator* allocator, ArchiveReader& archive)
      : _allocator {allocator}
      , _header {}
      , _entries {nullptr}
      , _data {nullptr}
      , _data_size {0} {
        auto archive_size = archive.Size();

        assert(allocator != nullptr);
        assert(archive_size < DoomWadMaximumSize);

        archive.Seek(0);
        archive& _header;

        auto entry_offset = _header.file_table_offset;
        auto entry_count  = _header.file_table_entries;

        assert(entry_offset < archive_size);
        archive.Seek(entry_offset);
        _entries = _allocator->AllocateContainer<DoomWadEntry>(entry_count);
        for (auto entry_index = uint32_t {0}; entry_index < entry_count; entry_index++) {
            auto& current_entry = _entries[entry_index];

            archive& current_entry;

            assert(current_entry.offset < archive_size);

            _data_size += current_entry.size;
        }

        assert(_data_size < archive_size);

        archive.Seek(sizeof(DoomWadHeader));
        _data = _allocator->AllocateContainer<uint8_t>(_data_size);
        archive.Serialize(_data, _data_size);
    }

    DoomWadReaderInternal::~DoomWadReaderInternal() {
        if (_data != nullptr) {
            _allocator->DeallocateContainer<uint8_t>(_data, _data_size);
            _data = nullptr;
        }

        if (_entries != nullptr) {
            _allocator->DeallocateContainer<DoomWadEntry>(_entries, _header.file_table_entries);
            _entries = nullptr;
        }

        _header    = DoomWadHeader {};
        _allocator = nullptr;
    }

    DoomWadSignature DoomWadReaderInternal::Signature() {
        return _header.signature;
    }

    uint32_t DoomWadReaderInternal::EntryCount() {
        return _header.file_table_entries;
    }

    uint32_t DoomWadReaderInternal::IndexForName(uint64_t name) {
        auto entry_count = EntryCount();

        for (auto entry_index = uint32_t {0}; entry_index < entry_count; entry_index++) {
            auto& current_entry = _entries[entry_index];

            if (current_entry.name == name) {
                return entry_index;
            }
        }

        return DoomWadInvalidEntry;
    }

    uint32_t DoomWadReaderInternal::IndexForNameAfter(uint64_t name, uint64_t start_name) {
        auto entry_count = EntryCount();
        auto start_index = IndexForName(start_name);

        if (start_index == DoomWadInvalidEntry) {
            return DoomWadInvalidEntry;
        }

        for (auto entry_index = start_index; entry_index < entry_count; entry_index++) {
            auto& current_entry = _entries[entry_index];

            if (current_entry.name == name) {
                return entry_index;
            }
        }

        return DoomWadInvalidEntry;
    }

    uint32_t DoomWadReaderInternal::IndexForNameBetween(uint64_t name, uint64_t prefix_name, uint64_t postfix_name) {
        auto prefix_index = IndexForName(prefix_name);
        if (prefix_index == DoomWadInvalidEntry) {
            return DoomWadInvalidEntry;
        }

        auto postfix_index = IndexForName(postfix_name);
        if (postfix_index == DoomWadInvalidEntry) {
            return DoomWadInvalidEntry;
        }

        // Skip over prefix entry.
        prefix_index++;

        for (auto entry_index = prefix_index; entry_index < postfix_index; entry_index++) {
            auto& current_entry = _entries[entry_index];

            if (current_entry.name == name) {
                return entry_index;
            }
        }

        return DoomWadInvalidEntry;
    }

    uint64_t DoomWadReaderInternal::IndexName(uint32_t index) {
        assert(index < EntryCount());

        return _entries[index].name;
    }

    uint32_t DoomWadReaderInternal::IndexSize(uint32_t index) {
        assert(index < EntryCount());

        return _entries[index].size;
    }

    MemoryArchiveReader DoomWadReaderInternal::IndexArchive(uint32_t index) {
        assert(index < EntryCount());

        auto entry        = _entries[index];
        auto entry_buffer = _data + entry.offset;
        auto entry_size   = entry.size;

        return MemoryArchiveReader {entry_buffer, entry_size};
    }
} // namespace wpieterse2825::scrapbook::game_tools::doom
