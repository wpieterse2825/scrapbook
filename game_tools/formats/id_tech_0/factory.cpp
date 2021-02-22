// SPDX-License-Identifier: GPL-3.0

#include "formats/id_tech_0/factory.hpp"

#include "formats/id_tech_0/internal/factory.hpp"

namespace wpieterse2825::game_tools::formats::id_tech_0 {
    static internal::FFactoryInternal id_tech_0_factory {};

    FFactory* GetFactory() {
        return &id_tech_0_factory;
    }
} // namespace wpieterse2825::game_tools::formats::id_tech_0
