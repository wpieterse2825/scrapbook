// SPDX-License-Identifier: GPL-3.0

#include <string.h>

#include "g3log/g3log.hpp"

#include "foundation/memory_archive_reader.hpp"

namespace wpieterse2825::game_tools {
    FMemoryArchiveReader::FMemoryArchiveReader(const uint8_t* buffer, size_t buffer_size)
      : FArchiveReader()
      , _buffer {buffer}
      , _buffer_size {buffer_size}
      , _buffer_location {0} {
        CHECK(buffer != nullptr) << "Passed in buffer in null.";
        CHECK(buffer_size != 0) << "Passed in buffer size is 0.";

        _is_read = true;
    }

    size_t FMemoryArchiveReader::Size() {
        return _buffer_size;
    }

    size_t FMemoryArchiveReader::Tell() {
        return _buffer_location;
    }

    void FMemoryArchiveReader::Seek(size_t location) {
        CHECK(location < _buffer_size) << "Trying to seek past buffer capacity.";

        _buffer_location = location;
    }

    void FMemoryArchiveReader::Serialize(void* buffer, size_t buffer_size) {
        CHECK(buffer_size != 0) << "Trying to read a zero sized buffer.";
        CHECK((_buffer_location + buffer_size) <= _buffer_size) << "Trying to read past buffer capacity.";

        auto read_location = _buffer + _buffer_location;

        ::memcpy(buffer, read_location, buffer_size);
        _buffer_location += buffer_size;
    }
} // namespace wpieterse2825::game_tools
