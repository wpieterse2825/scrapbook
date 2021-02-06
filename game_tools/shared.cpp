#include "game_tools/shared.hpp"

namespace wpieterse2825::scrapbook::game_tools {
    ReadFileResult ReadFile(const char* name) {
        auto file = fopen(name, "rb");

        fseek(file, 0, SEEK_END);
        auto buffer_size = (size_t)ftell(file);
        fseek(file, 0, SEEK_SET);

        auto buffer = static_cast<uint8_t*>(malloc(buffer_size));
        fread(buffer, buffer_size, 1, file);
        fclose(file);

        return {buffer, buffer_size};
    }
} // namespace wpieterse2825::scrapbook::game_tools
