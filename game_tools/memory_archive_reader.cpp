#include <assert.h>
#include <string.h>

#include "game_tools/memory_archive_reader.hpp"

namespace wpieterse2825::scrapbook::game_tools {
    MemoryArchiveReader::MemoryArchiveReader(const uint8_t* buffer, size_t buffer_size)
      : ArchiveReader()
      , _buffer {buffer}
      , _buffer_size {buffer_size}
      , _buffer_location {0} {
        assert(buffer != nullptr);
        assert(buffer_size != 0);

        _is_read = true;
    }

    size_t MemoryArchiveReader::Size() {
        return _buffer_size;
    }

    size_t MemoryArchiveReader::Tell() {
        return _buffer_location;
    }

    void MemoryArchiveReader::Seek(size_t location) {
        assert(location < _buffer_size);

        _buffer_location = location;
    }

    void MemoryArchiveReader::Serialize(void* buffer, size_t buffer_size) {
        assert(buffer_size != 0);
        assert((_buffer_location + buffer_size) <= _buffer_size);

        auto read_location = _buffer + _buffer_location;

        ::memcpy(buffer, read_location, buffer_size);
        _buffer_location += buffer_size;
    }
} // namespace wpieterse2825::scrapbook::game_tools
