#include <stdio.h>

#include <iostream>

#include "tools/cpp/runfiles/runfiles.h"

#include "game_tools/shared.hpp"
#include "game_tools/allocator.hpp"

#include "game_tools/doom/doom_factory.hpp"

using namespace bazel::tools::cpp::runfiles;

using namespace wpieterse2825::scrapbook::game_tools;

using namespace wpieterse2825::scrapbook::game_tools::doom;

void DisplayDetails(Allocator* allocator, DoomFactory* factory, const char* filename) {
    std::cout << " - Processing " << filename << " - ";

    auto [buffer, buffer_size] = ReadFile(filename);

    auto archive = MemoryArchiveReader {buffer, buffer_size};
    auto reader  = factory->CreateReader(allocator, archive);

    if (reader->Signature() == DoomWadSignature::Base) {
        std::cout << "Base" << std::endl;
    } else if (reader->Signature() == DoomWadSignature::Extension) {
        std::cout << "Extension" << std::endl;
    } else {
        std::cout << "Unknown" << std::endl;
    }

    auto entries = reader->EntryCount();
    for (auto entry_index = uint32_t {0}; entry_index < entries; entry_index++) {
        auto entry_name = reader->IndexName(entry_index);
        auto entry_size = reader->IndexSize(entry_index);

        std::cout << "   - " << DoomNameToString(entry_name) << " - " << entry_size << std::endl;
    }

    allocator->DeallocateObject(reader);
    buffer_size = 0;
    free(buffer);
}

void DisplayDetails(Allocator* allocator, DoomFactory* factory, const std::string& filename) {
    DisplayDetails(allocator, factory, filename.c_str());
}

int main(int argument_count, char** arguments) {
    auto runfiles_error = std::string {""};
    auto runfiles       = std::unique_ptr<Runfiles> {Runfiles::Create(arguments[0], &runfiles_error)};

    std::cout << "DOOM WAD Information:" << std::endl;

    if (runfiles == nullptr) {
        std::cout << "ERROR: Failed to initialize run-files : " << runfiles_error << std::endl;
        return 1;
    }

    auto allocator = GetSystemAllocator();
    auto factory   = GetDoomFactory();

    DisplayDetails(allocator, factory, runfiles->Rlocation("scrapbook/game_tools/data/doom/DOOM.WAD"));

    return 0;
}
