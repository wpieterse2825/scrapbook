// SPDX-License-Identifier: GPL-3.0

#include "games/doom_1/factory.hpp"

namespace wpieterse2825::game_tools::games::doom_1 {
    FFactory* GetFactory() {
        return formats::id_tech_0::GetFactory();
    }
} // namespace wpieterse2825::game_tools::games::doom_1
