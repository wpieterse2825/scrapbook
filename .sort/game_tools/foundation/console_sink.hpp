#pragma once

#include <iostream>

#include "g3log/g3log.hpp"

namespace wpieterse2825::game_tools {
    class FConsoleSink {
      public:
        void ReceiveLogMessage(g3::LogMessageMover logEntry) {
            auto level = logEntry.get()._level;

            std::cout << logEntry.get().toString();
        }
    };
} // namespace wpieterse2825::game_tools
