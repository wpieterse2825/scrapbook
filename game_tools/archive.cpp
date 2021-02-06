#include "game_tools/archive.hpp"

namespace wpieterse2825::scrapbook::game_tools {
    Archive::Archive()
      : _is_read {false}
      , _is_write {false} {
    }

    bool Archive::IsRead() {
        return _is_read;
    }

    bool Archive::IsWrite() {
        return _is_write;
    }
} // namespace wpieterse2825::scrapbook::game_tools
