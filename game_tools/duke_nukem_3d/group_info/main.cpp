#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <cassert>
#include <memory>
#include <array>
#include <vector>
#include <iostream>
#include <fstream>

#include "tools/cpp/runfiles/runfiles.h"

using bazel::tools::cpp::runfiles::Runfiles;

class Exception {
  public:
};

class OutOfMemoryException : public Exception {
  public:
};

class IOException : public Exception {
  public:
};

class OpenIOException : public Exception {
  public:
};

class ReadIOException : public Exception {
  public:
};

class InvalidFormatException : public Exception {
  public:
};

class InvalidSignatureException : public InvalidFormatException {
  public:
};

class VirtualBase {
  public:
    virtual ~VirtualBase() {
    }
};

struct BuildGroupFileEntry {
    std::array<char, 16> name;
    uint32_t             size;
    uint8_t*             buffer;

    BuildGroupFileEntry()
      : name {}
      , size {0}
      , buffer {nullptr} {
    }
};

class BuildGroupFileIterator : public VirtualBase {
  public:
    BuildGroupFileIterator(BuildGroupFileEntry* entries, uint32_t entry_count);

    bool IsDone();
    void Next();

    BuildGroupFileEntry* GetCurrentEntry();

  private:
    BuildGroupFileEntry* _current_entry;
    BuildGroupFileEntry* _last_entry;
};

BuildGroupFileIterator::BuildGroupFileIterator(BuildGroupFileEntry* entries, uint32_t entry_count)
  : _current_entry {entries}
  , _last_entry {entries + entry_count} {
}

bool BuildGroupFileIterator::IsDone() {
    return _current_entry == _last_entry;
}

void BuildGroupFileIterator::Next() {
    _current_entry++;
}

BuildGroupFileEntry* BuildGroupFileIterator::GetCurrentEntry() {
    return _current_entry;
}

class BuildGroupFile : public VirtualBase {
  public:
    virtual BuildGroupFileIterator Iterate() = 0;
};

class DukeNukem3DFactory : public VirtualBase {
  public:
    virtual std::unique_ptr<BuildGroupFile> LoadArchive(const uint8_t* buffer, size_t buffer_length) = 0;
    virtual std::unique_ptr<BuildGroupFile> LoadArchive(const std::string& filename)                 = 0;
};

struct BuildGroupFileHeaderInternal {
    uint8_t  signature[12];
    uint32_t entry_count;
};

struct BuildGroupFileEntryInternal {
    uint8_t  filename[12];
    uint32_t size;
};

class DukeNukem3DGroupFile : public BuildGroupFile {
  public:
    virtual void Load(const uint8_t* buffer, size_t buffer_length);
    virtual void Load(const std::string& filename);

    virtual BuildGroupFileIterator Iterate() override;

  private:
    uint32_t                               _entry_count;
    std::unique_ptr<BuildGroupFileEntry[]> _entries_cover;
    std::unique_ptr<uint8_t[]>             _buffer_cover;
};

void DukeNukem3DGroupFile::Load(const uint8_t* buffer, size_t buffer_length) {
    auto input_header  = reinterpret_cast<const BuildGroupFileHeaderInternal*>(buffer);
    auto input_entries = reinterpret_cast<const BuildGroupFileEntryInternal*>(buffer + sizeof(BuildGroupFileHeaderInternal));

    // TODO(wpieterse): Verify signature.

    _entry_count = input_header->entry_count;

    auto output_buffer_size = 0;
    for (auto entry_index = uint32_t {0}; entry_index < _entry_count; entry_index++) {
        auto input_entry = input_entries[entry_index];

        output_buffer_size += input_entry.size;
    }

    _entries_cover      = std::make_unique<BuildGroupFileEntry[]>(_entry_count);
    auto output_entries = _entries_cover.get();
    if (output_entries == nullptr) {
        throw OutOfMemoryException {};
    }

    _buffer_cover      = std::make_unique<uint8_t[]>(output_buffer_size);
    auto output_buffer = _buffer_cover.get();
    if (output_buffer == nullptr) {
        throw OutOfMemoryException {};
    }

    auto input_buffer_offset  = sizeof(BuildGroupFileHeaderInternal) + (sizeof(BuildGroupFileEntryInternal) * _entry_count);
    auto output_buffer_offset = 0;
    for (auto entry_index = uint32_t {0}; entry_index < _entry_count; entry_index++) {
        auto& input_entry  = input_entries[entry_index];
        auto& output_entry = output_entries[entry_index];

        for (auto name_index = 0; name_index < 12; name_index++) {
            output_entry.name[name_index] = input_entry.filename[name_index];
        }

        output_entry.size   = input_entry.size;
        output_entry.buffer = output_buffer + output_buffer_offset;

        ::memcpy(output_entry.buffer, buffer + input_buffer_offset, input_entry.size);

        input_buffer_offset += input_entry.size;
        output_buffer_offset += input_entry.size;
    }
}

void DukeNukem3DGroupFile::Load(const std::string& filename) {
    std::fstream input_file {filename, std::ios::in | std::ios::binary | std::ios::ate};
    if (input_file.is_open() == false) {
        throw OpenIOException {};
    }

    auto input_buffer_size  = input_file.tellg();
    auto input_buffer_cover = std::make_unique<uint8_t[]>(input_buffer_size);
    auto input_buffer       = input_buffer_cover.get();
    if (input_buffer == nullptr) {
        throw OutOfMemoryException {};
    }

    input_file.seekg(0, std::ios::beg);
    input_file.read(reinterpret_cast<char*>(input_buffer), input_buffer_size);
    if (input_file.bad() == true) {
        throw ReadIOException {};
    }

    Load(input_buffer, input_buffer_size);
}

BuildGroupFileIterator DukeNukem3DGroupFile::Iterate() {
    return BuildGroupFileIterator {_entries_cover.get(), _entry_count};
}

class DukeNukem3DFactoryInternal final : public DukeNukem3DFactory {
  public:
    virtual std::unique_ptr<BuildGroupFile> LoadArchive(const uint8_t* buffer, size_t buffer_length) override;
    virtual std::unique_ptr<BuildGroupFile> LoadArchive(const std::string& filename) override;
};

std::unique_ptr<BuildGroupFile> DukeNukem3DFactoryInternal::LoadArchive(const uint8_t* buffer, size_t buffer_length) {
    auto group_file = new DukeNukem3DGroupFile {};

    try {
        group_file->Load(buffer, buffer_length);
    } catch (...) {
        delete group_file;
        throw;
    }

    return std::unique_ptr<BuildGroupFile> {group_file};
}

std::unique_ptr<BuildGroupFile> DukeNukem3DFactoryInternal::LoadArchive(const std::string& filename) {
    auto group_file = new DukeNukem3DGroupFile {};

    try {
        group_file->Load(filename);
    } catch (...) {
        delete group_file;
        throw;
    }

    return std::unique_ptr<BuildGroupFile> {group_file};
}

bool DisplayStatistics(DukeNukem3DFactory* group_factory, const std::string& filename) {
    std::cout << " - Parsing " << filename << std::endl;

    try {
        auto group_file = group_factory->LoadArchive(filename);

        for (auto iterator = group_file->Iterate(); iterator.IsDone() == false; iterator.Next()) {
            auto current_entry = iterator.GetCurrentEntry();

            std::cout << "     - " << current_entry->name.begin() << " - " << current_entry->size << " - " << reinterpret_cast<void*>(current_entry->buffer)
                      << std::endl;
        }
    } catch (const std::exception& exception) {
        std::cout << "ERROR : " << exception.what() << std::endl;
        return false;
    }

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

    auto group_file_factory = DukeNukem3DFactoryInternal {};

    // if (DisplayStatistics(&group_file_factory, runfiles->Rlocation("scrapbook/game_tools/data/duke_nukem_3d/nwinter.grp")) == false) {
    //     return 1;
    // }

    if (DisplayStatistics(&group_file_factory, runfiles->Rlocation("scrapbook/game_tools/data/duke_nukem_3d/duke3d.grp")) == false) {
        return 1;
    }

    // if (DisplayStatistics(&group_file_factory, runfiles->Rlocation("scrapbook/game_tools/data/duke_nukem_3d/dukedc.grp")) == false) {
    //     return 1;
    // }

    // if (DisplayStatistics(&group_file_factory, runfiles->Rlocation("scrapbook/game_tools/data/duke_nukem_3d/vacation.grp")) == false) {
    //     return 1;
    // }

    return 0;
}
