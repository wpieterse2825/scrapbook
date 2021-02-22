// SPDX-License-Identifier: GPL-3.0

#include <string.h>

#include "g3log/g3log.hpp"

#include "foundation/memory_archive_writer.hpp"

namespace wpieterse2825::game_tools {
    FMemoryArchiveWriter::FMemoryArchiveWriter(uint8_t* buffer, size_t buffer_size)
      : FArchiveWriter()
      , _buffer {buffer}
      , _buffer_size {buffer_size}
      , _buffer_location {0} {
        CHECK(buffer != nullptr) << "Passed in buffer in null.";
        CHECK(buffer_size != 0) << "Passed in buffer size is 0.";

        _is_write = true;
    }

    size_t FMemoryArchiveWriter::Size() {
        return _buffer_size;
    }

    size_t FMemoryArchiveWriter::Tell() {
        return _buffer_location;
    }

    void FMemoryArchiveWriter::Seek(size_t location) {
        CHECK(location < _buffer_size) << "Trying to seek past buffer capacity.";

        _buffer_location = location;
    }

    void FMemoryArchiveWriter::Serialize(void* buffer, size_t buffer_size) {
        CHECK(buffer_size != 0) << "Trying to write a zero sized buffer.";
        CHECK((_buffer_location + buffer_size) <= _buffer_size) << "Trying to write past buffer capacity.";

        auto write_location = _buffer + _buffer_location;

        ::memcpy(write_location, buffer, buffer_size);
        _buffer_location += buffer_size;
    }
} // namespace wpieterse2825::game_tools
