#include <assert.h>
#include <string.h>

#include "game_tools/memory_archive_writer.hpp"

namespace wpieterse2825::scrapbook::game_tools {
    MemoryArchiveWriter::MemoryArchiveWriter(uint8_t* buffer, size_t buffer_size)
      : ArchiveWriter()
      , _buffer {buffer}
      , _buffer_size {buffer_size}
      , _buffer_location {0} {
        assert(buffer != nullptr);
        assert(buffer_size != 0);

        _is_write = true;
    }

    size_t MemoryArchiveWriter::Size() {
        return _buffer_size;
    }

    size_t MemoryArchiveWriter::Tell() {
        return _buffer_location;
    }

    void MemoryArchiveWriter::Seek(size_t location) {
        assert(location < _buffer_size);

        _buffer_location = location;
    }

    void MemoryArchiveWriter::Serialize(void* buffer, size_t buffer_size) {
        assert(buffer_size != 0);
        assert((_buffer_location + buffer_size) <= _buffer_size);

        auto write_location = _buffer + _buffer_location;

        ::memcpy(write_location, buffer, buffer_size);
        _buffer_location += buffer_size;
    }
} // namespace wpieterse2825::scrapbook::game_tools
