#include <stdint.h>
#include <stdio.h>
#include <iostream>

#include "tools/cpp/runfiles/runfiles.h"

using bazel::tools::cpp::runfiles::Runfiles;

struct GroupFileHeader {
    uint8_t  signature[12];
    uint32_t entries;
};

struct GroupFileEntry {
    uint8_t  filename[12];
    uint32_t size;
};

bool DisplayStatistics(const std::string& name) {
    auto group_file = ::fopen(name.c_str(), "rb");
    if (group_file == nullptr) {
        std::cout << "ERROR: Failed to open group file : " << name << std::endl;
        return false;
    }

    ::fseek(group_file, 0, SEEK_END);
    auto group_file_size = ::ftell(group_file);
    ::fseek(group_file, 0, SEEK_SET);

    std::cout << " - Enumerating " << name << " (" << group_file_size << ")" << std::endl;

    auto group_data = static_cast<uint8_t*>(::malloc(group_file_size));
    if (group_data == nullptr) {
        std::cout << "ERROR: Failed to allocate memory for group file : " << name << " (" << group_file_size << ")" << std::endl;
        return false;
    }

    ::fread(group_data, group_file_size, 1, group_file);

    auto header  = reinterpret_cast<GroupFileHeader*>(group_data);
    auto entries = reinterpret_cast<GroupFileEntry*>(group_data + sizeof(GroupFileHeader));

    std::cout << "   - Entries (" << header->entries << "):" << std::endl;
    for (uint32_t index = 0; index < header->entries; index++) {
        auto current_entry = entries[index];

        std::cout << "     - ";
        for (auto name_index = 0; name_index < 12; name_index++) {
            std::cout << current_entry.filename[name_index];
        }

        std::cout << " - " << current_entry.size << std::endl;
    }

    ::free(group_data);
    ::fclose(group_file);
    return true;
}

int main(int argument_count, char** arguments) {
    std::string               runfiles_error {""};
    std::unique_ptr<Runfiles> runfiles {Runfiles::Create(arguments[0], &runfiles_error)};

    std::cout << "Duke Nukem 3D Group Information:" << std::endl;

    if (runfiles == nullptr) {
        std::cout << "ERROR: Failed to initialize run-files : " << runfiles_error << std::endl;
        return 1;
    }

    if (!DisplayStatistics(runfiles->Rlocation("scrapbook/game_tools/data/duke_nukem_3d/nwinter.grp"))) {
        return 1;
    }

    if (!DisplayStatistics(runfiles->Rlocation("scrapbook/game_tools/data/duke_nukem_3d/duke3d.grp"))) {
        return 1;
    }

    if (!DisplayStatistics(runfiles->Rlocation("scrapbook/game_tools/data/duke_nukem_3d/dukedc.grp"))) {
        return 1;
    }

    if (!DisplayStatistics(runfiles->Rlocation("scrapbook/game_tools/data/duke_nukem_3d/vacation.grp"))) {
        return 1;
    }

    return 0;
}
