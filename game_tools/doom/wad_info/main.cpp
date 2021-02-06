#include <assert.h>
#include <string.h>
#include <array>
#include <iostream>

#include "tools/cpp/runfiles/runfiles.h"

using bazel::tools::cpp::runfiles::Runfiles;

namespace wad {
    constexpr uint32_t InvalidWADEntry = 0xFFFFFFFF;

    enum class idWADFileSignature : uint32_t {
        Base      = 0x44415749,
        Extension = 0x44415750,
    };

    struct idWADFileHeader {
        idWADFileSignature signature;
        uint32_t           file_table_entries;
        uint32_t           file_table_offset;
    };

    struct idWADFileEntry {
        uint32_t offset;
        uint32_t size;
        uint64_t name;
    };

    struct idWADFile {
        uint8_t* buffer;
        size_t   buffer_size;

        idWADFileHeader* header;
        idWADFileEntry*  entries;

        bool is_valid;
        bool is_signature_valid;
    };

    namespace file_header {
        idWADFileSignature Signature(idWADFileHeader* header) {
            return header->signature;
        }

        bool IsBaseSignature(idWADFileHeader* header) {
            return file_header::Signature(header) == idWADFileSignature::Base;
        }

        bool IsExtensionSignature(idWADFileHeader* header) {
            return file_header::Signature(header) == idWADFileSignature::Extension;
        }

        uint32_t FileTableEntries(idWADFileHeader* header) {
            return header->file_table_entries;
        }

        uint32_t FileTableOffset(idWADFileHeader* header) {
            return header->file_table_offset;
        }
    } // namespace file_header

    namespace file_entry {
        uint32_t Offset(idWADFileEntry* entry) {
            return entry->offset;
        }

        uint32_t Size(idWADFileEntry* entry) {
            return entry->size;
        }

        uint64_t Name(idWADFileEntry* entry) {
            return entry->name;
        }
    } // namespace file_entry

    namespace file {
        idWADFile Open(uint8_t* buffer, size_t buffer_size) {
            auto result = idWADFile {};

            result.buffer      = buffer;
            result.buffer_size = buffer_size;

            result.header = (idWADFileHeader*)(buffer);

            bool is_base      = file_header::IsBaseSignature(result.header);
            bool is_extension = file_header::IsExtensionSignature(result.header);
            if (is_base == true || is_extension == true) {
                result.is_signature_valid = true;
            }

            if (result.is_signature_valid == true) {
                result.entries = (idWADFileEntry*)(buffer + result.header->file_table_offset);

                result.is_valid = true;
            }

            return result;
        }

        uint8_t* Buffer(idWADFile* wad_file) {
            return wad_file->buffer;
        }

        size_t BufferSize(idWADFile* wad_file) {
            return wad_file->buffer_size;
        }

        idWADFileHeader* Header(idWADFile* wad_file) {
            return wad_file->header;
        }

        idWADFileEntry* Entries(idWADFile* wad_file) {
            return wad_file->entries;
        }

        bool IsValid(idWADFile* wad_file) {
            return wad_file->is_valid;
        }

        bool IsSignatureValid(idWADFile* wad_file) {
            return wad_file->is_signature_valid;
        }

        uint32_t EntryCount(idWADFile* wad_file) {
            auto header      = file::Header(wad_file);
            auto entry_count = file_header::FileTableEntries(header);

            return entry_count;
        }

        idWADFileEntry* EntryForIndex(idWADFile* wad_file, uint32_t index) {
            auto entries = file::Entries(wad_file);

            return &entries[index];
        }

        uint32_t IndexForEntry(idWADFile* wad_file, idWADFileEntry* entry) {
            auto entry_count = file::EntryCount(wad_file);

            for (auto entry_index = uint32_t {0}; entry_count; entry_index++) {
                auto current_entry = file::EntryForIndex(wad_file, entry_index);

                if (current_entry == entry) {
                    return entry_index;
                }
            }

            return InvalidWADEntry;
        }

        idWADFileEntry* EntryForName(idWADFile* wad_file, uint64_t name) {
            auto entry_count = file::EntryCount(wad_file);

            for (auto entry_index = uint32_t {0}; entry_index < entry_count; entry_index++) {
                auto current_entry = file::EntryForIndex(wad_file, entry_index);

                if (file_entry::Name(current_entry) == name) {
                    return current_entry;
                }
            }

            return nullptr;
        }

        uint32_t IndexForName(idWADFile* wad_file, uint64_t name) {
            auto entry = file::EntryForName(wad_file, name);
            auto index = file::IndexForEntry(wad_file, entry);

            return index;
        }

        idWADFileEntry* EntryForNameAfter(idWADFile* wad_file, uint64_t name, uint64_t start_name) {
            auto entry_count = file::EntryCount(wad_file);
            auto start_index = file::IndexForName(wad_file, start_name);

            if (start_index == InvalidWADEntry) {
                return nullptr;
            }

            for (auto entry_index = start_index; entry_index < entry_count; entry_index++) {
                auto current_entry = file::EntryForIndex(wad_file, entry_index);

                if (file_entry::Name(current_entry) == name) {
                    return current_entry;
                }
            }

            return nullptr;
        }

        idWADFileEntry* EntryForNameBetween(idWADFile* wad_file, uint64_t name, uint64_t prefix_name, uint64_t postfix_name) {
            auto prefix_index  = file::IndexForName(wad_file, prefix_name);
            auto postfix_index = file::IndexForName(wad_file, postfix_name);

            if (prefix_index == InvalidWADEntry) {
                return nullptr;
            }

            if (postfix_index == InvalidWADEntry) {
                return nullptr;
            }

            // Skip over prefix entry.
            prefix_index++;

            for (auto entry_index = prefix_index; entry_index < postfix_index; entry_index++) {
                auto current_entry = file::EntryForIndex(wad_file, entry_index);

                if (file_entry::Name(current_entry) == name) {
                    return current_entry;
                }
            }

            return nullptr;
        }

        uint8_t* DataForEntry(idWADFile* wad_file, idWADFileEntry* entry) {
            auto buffer       = file::Buffer(wad_file);
            auto entry_offset = file_entry::Offset(entry);

            return buffer + entry_offset;
        }

        uint64_t StringToIndex(const char* name) {
            auto name_length    = strlen(name);
            auto name_converted = std::array<uint8_t, 8> {};

            for (auto name_index = size_t {0}; name_index < name_length; name_index++) {
                name_converted[name_index] = name[name_index];
            }

            auto part_0 = uint64_t {name_converted[0]} << 0;
            auto part_1 = uint64_t {name_converted[1]} << 8;
            auto part_2 = uint64_t {name_converted[2]} << 16;
            auto part_3 = uint64_t {name_converted[3]} << 24;
            auto part_4 = uint64_t {name_converted[4]} << 32;
            auto part_5 = uint64_t {name_converted[5]} << 40;
            auto part_6 = uint64_t {name_converted[6]} << 48;
            auto part_7 = uint64_t {name_converted[7]} << 56;

            return part_0 | part_1 | part_2 | part_3 | part_4 | part_5 | part_6 | part_7;
        }
    } // namespace file
} // namespace wad

struct ReadFileResult {
    uint8_t* buffer;
    size_t   buffer_size;
};

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

void DisplayDetails(const std::string& filename) {
    std::cout << " - Processing " << filename;

    auto [buffer, buffer_size] = ReadFile(filename.c_str());
    auto file                  = wad::file::Open(buffer, buffer_size);
    auto entries               = wad::file::EntryCount(&file);

    if (file.is_valid == false) {
        std::cout << " - Invalid" << std::endl;
        return;
    }

    if (file.is_signature_valid == false) {
        std::cout << " - Invalid Signature" << std::endl;
        return;
    }

    auto header    = wad::file::Header(&file);
    auto signature = wad::file_header::Signature(header);
    if (signature == wad::idWADFileSignature::Base) {
        std::cout << " - Base" << std::endl;
    } else if (signature == wad::idWADFileSignature::Extension) {
        std::cout << " - Extension" << std::endl;
    } else {
        std::cout << " - Unknown" << std::endl;
    }

    /*
    for (auto entry_index = uint32_t {0}; entry_index < entries; entry_index++) {
        auto current_entry = wad::file::EntryForIndex(&file, entry_index);
        char name_user[8]  = {0};

        name_user[0] = (current_entry->name >> 0) & 0xFF;
        name_user[1] = (current_entry->name >> 8) & 0xFF;
        name_user[2] = (current_entry->name >> 16) & 0xFF;
        name_user[3] = (current_entry->name >> 24) & 0xFF;
        name_user[4] = (current_entry->name >> 32) & 0xFF;
        name_user[5] = (current_entry->name >> 40) & 0xFF;
        name_user[6] = (current_entry->name >> 48) & 0xFF;
        name_user[7] = (current_entry->name >> 56) & 0xFF;

        std::cout << "   - ";
        for (auto name_index = 0; name_index < 8; name_index++) {
            std::cout << name_user[name_index];
        }

        std::cout << " - " << current_entry->offset << " - " << current_entry->size << std::endl;
    }
    */

    buffer_size = 0;
    free(buffer);
}

int main(int argument_count, char** arguments) {
    std::string               runfiles_error {""};
    std::unique_ptr<Runfiles> runfiles {Runfiles::Create(arguments[0], &runfiles_error)};

    std::cout << "DOOM WAD Information:" << std::endl;

    if (runfiles == nullptr) {
        std::cout << "ERROR: Failed to initialize run-files : " << runfiles_error << std::endl;
        return 1;
    }

    DisplayDetails(runfiles->Rlocation("scrapbook/game_tools/data/doom/DOOM.WAD"));
    return 0;
}
