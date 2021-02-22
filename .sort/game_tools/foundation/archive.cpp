// SPDX-License-Identifier: GPL-3.0

#include "foundation/archive.hpp"

namespace wpieterse2825::game_tools {
    FArchive::FArchive()
      : _is_read {false}
      , _is_write {false} {
    }

    bool FArchive::IsRead() {
        return _is_read;
    }

    bool FArchive::IsWrite() {
        return _is_write;
    }
} // namespace wpieterse2825::game_tools
