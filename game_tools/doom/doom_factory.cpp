#include "game_tools/doom/doom_factory.hpp"

#include "game_tools/doom/doom_factory_internal.hpp"

namespace wpieterse2825::scrapbook::game_tools::doom {
    static DoomFactoryInternal doom_factory {};

    DoomFactory* GetDoomFactory() {
        return &doom_factory;
    }
} // namespace wpieterse2825::scrapbook::game_tools::doom
