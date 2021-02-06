#include <iostream>

#include "tools/cpp/runfiles/runfiles.h"

#include "game_tools/shared.hpp"
#include "game_tools/allocator.hpp"
#include "game_tools/archive_writer.hpp"
#include "game_tools/memory_archive_reader.hpp"

using namespace bazel::tools::cpp::runfiles;

using namespace wpieterse2825::scrapbook::game_tools;

class DukeNukem3DGroupReader : public VirtualBase {
  public:
    virtual std::array<char, 12> Signature()  = 0;
    virtual uint32_t             EntryCount() = 0;

    virtual uint32_t IndexForName(uint64_t name)                                                     = 0;
    virtual uint32_t IndexForNameAfter(uint64_t name, uint64_t start_name)                           = 0;
    virtual uint32_t IndexForNameBetween(uint64_t name, uint64_t prefix_name, uint64_t postfix_name) = 0;

    virtual uint64_t            IndexName(uint32_t index)    = 0;
    virtual uint32_t            IndexSize(uint32_t index)    = 0;
    virtual MemoryArchiveReader IndexArchive(uint32_t index) = 0;
};

class DukeNukem3DGroupReaderInternal : public DukeNukem3DGroupReader {
  public:
    virtual std::array<char, 12> Signature() override {
        auto result = std::array<char, 12> {};
        return result;
    }

    virtual uint32_t EntryCount() {
        return 0;
    }

    virtual uint32_t IndexForName(uint64_t name) override {
        return 0;
    }

    virtual uint32_t IndexForNameAfter(uint64_t name, uint64_t start_name) override {
        return 0;
    }

    virtual uint32_t IndexForNameBetween(uint64_t name, uint64_t prefix_name, uint64_t postfix_name) override {
        return 0;
    }

    virtual uint64_t IndexName(uint32_t index) override {
        return 0;
    }

    virtual uint32_t IndexSize(uint32_t index) override {
        return 0;
    }

    virtual MemoryArchiveReader IndexArchive(uint32_t index) override {
        return MemoryArchiveReader {nullptr, 0};
    }
};

class DukeNukem3DGroupBuilder : public VirtualBase {
  public:
};

class DukeNukem3DGroupBuilderArchive : public DukeNukem3DGroupBuilder {
  public:
    virtual size_t GetSize() = 0;

    virtual void Finalize(ArchiveWriter& archive) = 0;
    virtual void Reset()                          = 0;
};

class DukeNukem3DGroupBuilderArchiveInternal : public DukeNukem3DGroupBuilderArchive {
  public:
    virtual size_t GetSize() override {
        return 0;
    }

    virtual void Finalize(ArchiveWriter& archive) {
    }
    virtual void Reset() {
    }
};

class DukeNukem3DFactory : public VirtualBase {
  public:
    virtual DukeNukem3DGroupReader*         CreateGroupReader(Allocator* allocator, ArchiveReader& archive) = 0;
    virtual DukeNukem3DGroupBuilderArchive* CreateGroupBuilderArchive(Allocator* allocator)                 = 0;
};

class DukeNukem3DFactoryInternal : public DukeNukem3DFactory {
  public:
    virtual DukeNukem3DGroupReader* CreateGroupReader(Allocator* allocator, ArchiveReader& archive) override {
        return nullptr;
    }

    virtual DukeNukem3DGroupBuilderArchive* CreateGroupBuilderArchive(Allocator* allocator) override {
        return nullptr;
    }
};

static DukeNukem3DFactoryInternal duke_nukem_3d_factory {};

DukeNukem3DFactory* GetDukeNukem3DFactory() {
    return &duke_nukem_3d_factory;
}

void DisplayDetails(Allocator* allocator, DukeNukem3DFactory* group_factory, const char* filename) {
    std::cout << " - Parsing " << filename << std::endl;

    auto [buffer, buffer_size] = ReadFile(filename);
    auto archive               = MemoryArchiveReader {buffer, buffer_size};

    buffer_size = 0;
    ::free(buffer);
}

void DisplayDetails(Allocator* allocator, DukeNukem3DFactory* factory, const std::string& filename) {
    DisplayDetails(allocator, factory, filename.c_str());
}

int main(int argument_count, char** arguments) {
    auto runfiles_error = std::string {""};
    auto runfiles       = std::unique_ptr<Runfiles> {Runfiles::Create(arguments[0], &runfiles_error)};

    std::cout << "Duke Nukem 3D Group Information:" << std::endl;

    if (runfiles == nullptr) {
        std::cout << "ERROR: Failed to initialize run-files : " << runfiles_error << std::endl;
        return 1;
    }

    auto allocator = GetSystemAllocator();
    auto factory   = GetDukeNukem3DFactory();

    DisplayDetails(allocator, factory, runfiles->Rlocation("scrapbook/game_tools/data/duke_nukem_3d/duke3d.grp"));

    return 0;
}
