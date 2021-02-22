// SPDX-License-Identifier: GPL-3.0

#include "g3log/g3log.hpp"
#include "g3log/logworker.hpp"

#include "tools/cpp/runfiles/runfiles.h"

#include "foundation/console_sink.hpp"
#include "foundation/utilities.hpp"
#include "foundation/allocator.hpp"
#include "foundation/memory_archive_reader.hpp"
#include "foundation/memory_archive_writer.hpp"

using namespace g3;

using namespace bazel::tools::cpp::runfiles;

using namespace wpieterse2825::game_tools;

struct FHeader {
    char     signature[12];
    uint32_t entry_count;
};

static inline FArchive& operator&(FArchive& archive, FHeader& value) {
    archive.Serialize(value.signature, 12);

    archive& value.entry_count;

    return archive;
}

struct FEntry {
    char     name[12];
    uint32_t size;
};

static inline FArchive& operator&(FArchive& archive, FEntry& value) {
    archive.Serialize(value.name, 12);

    archive& value.size;

    return archive;
}

class FBuilder : public FVirtualBase {
  public:
};

class FBuilderArchive : public FBuilder {
  public:
    virtual size_t GetSize() = 0;

    virtual void Finalize(FArchiveWriter& archive) = 0;
    virtual void Reset()                           = 0;
};

class FBuilderArchiveInternal : public FBuilderArchive {
  public:
    FBuilderArchiveInternal(FAllocator* allocator)
      : _allocator {allocator} {
        CHECK(_allocator != nullptr) << "Allocator cannot be null.";
    }

    virtual ~FBuilderArchiveInternal() {
        _allocator = nullptr;
    }

    virtual size_t GetSize() override {
        return 0;
    }

    virtual void Finalize(FArchiveWriter& archive) {
    }

    virtual void Reset() {
    }

  private:
    FAllocator* _allocator;
};

class FReader : public FVirtualBase {
  public:
    virtual std::array<char, 13> Signature()  = 0;
    virtual uint32_t             EntryCount() = 0;

    virtual uint32_t IndexForName(uint64_t name) = 0;

    virtual std::array<char, 13> IndexName(uint32_t index)    = 0;
    virtual uint32_t             IndexSize(uint32_t index)    = 0;
    virtual FMemoryArchiveReader IndexArchive(uint32_t index) = 0;
};

class FReaderInternal : public FReader {
  public:
    FReaderInternal(FAllocator* allocator, FArchiveReader& archive)
      : _allocator {allocator}
      , _header {}
      , _entries {nullptr}
      , _offsets {nullptr}
      , _data {nullptr}
      , _data_size {0} {
        CHECK(_allocator != nullptr) << "Allocator cannot be null.";

        archive& _header;

        // TODO(wpieterse): Verify signature.

        auto entry_count = _header.entry_count;

        _entries = _allocator->AllocateContainer<FEntry>(entry_count);
        _offsets = _allocator->AllocateContainer<size_t>(entry_count);
        for (auto entry_index = uint32_t {0}; entry_index < entry_count; entry_index++) {
            auto& current_entry = _entries[entry_index];

            archive& current_entry;

            _offsets[entry_index] = _data_size;
            _data_size += current_entry.size;
        }

        _data = _allocator->AllocateContainer<uint8_t>(_data_size);
        archive.Serialize(_data, _data_size);
    }

    virtual ~FReaderInternal() {
        if (_data != nullptr) {
            _allocator->DeallocateContainer<uint8_t>(_data, _data_size);
            _data = nullptr;
        }

        if (_offsets != nullptr) {
            _allocator->DeallocateContainer<size_t>(_offsets, _header.entry_count);
            _offsets = nullptr;
        }

        if (_entries != nullptr) {
            _allocator->DeallocateContainer<FEntry>(_entries, _header.entry_count);
            _entries = nullptr;
        }

        _data_size = 0;
        _header    = FHeader {};
        _allocator = nullptr;
    }

    virtual std::array<char, 13> Signature() override {
        auto result = std::array<char, 13> {};

        for (auto result_index = 0; result_index < 12; result_index++) {
            result[result_index] = _header.signature[result_index];
        }

        return result;
    }

    virtual uint32_t EntryCount() {
        return _header.entry_count;
    }

    virtual uint32_t IndexForName(uint64_t name) override {
        return 0;
    }

    virtual std::array<char, 13> IndexName(uint32_t index) override {
        CHECK(index < EntryCount()) << "Index is out of bounds.";

        auto  result = std::array<char, 13> {};
        auto& entry  = _entries[index];

        for (auto result_index = 0; result_index < 12; result_index++) {
            result[result_index] = entry.name[result_index];
        }

        return result;
    }

    virtual uint32_t IndexSize(uint32_t index) override {
        CHECK(index < EntryCount()) << "Index is out of bounds.";

        return _entries[index].size;
    }

    virtual FMemoryArchiveReader IndexArchive(uint32_t index) override {
        return FMemoryArchiveReader {nullptr, 0};
    }

  private:
    FAllocator* _allocator;

    FHeader  _header;
    FEntry*  _entries;
    size_t*  _offsets;
    uint8_t* _data;
    size_t   _data_size;
};

class FFactory : public FVirtualBase {
  public:
    virtual FReader*         CreateGroupReader(FAllocator* allocator, FArchiveReader& archive) = 0;
    virtual FBuilderArchive* CreateGroupBuilderArchive(FAllocator* allocator)                  = 0;
};

class FFactoryInternal : public FFactory {
  public:
    virtual FReader* CreateGroupReader(FAllocator* allocator, FArchiveReader& archive) override {
        return allocator->AllocateObject<FReaderInternal>(allocator, archive);
    }

    virtual FBuilderArchive* CreateGroupBuilderArchive(FAllocator* allocator) override {
        return allocator->AllocateObject<FBuilderArchiveInternal>(allocator);
    }
};

static FFactoryInternal build_factory {};

FFactory* GetFactory() {
    return &build_factory;
}

void DisplayDetails(FAllocator* allocator, FFactory* factory, const char* filename) {
    LOG(INFO) << "Processing " << filename;

    auto buffer_size = size_t {0};
    auto buffer      = ReadCompleteFile(allocator, filename, &buffer_size);
    auto archive     = FMemoryArchiveReader {buffer, buffer_size};
    auto reader      = factory->CreateGroupReader(allocator, archive);

    auto entries = reader->EntryCount();
    for (auto entry_index = uint32_t {0}; entry_index < entries; entry_index++) {
        auto entry_name = reader->IndexName(entry_index);
        auto entry_size = reader->IndexSize(entry_index);

        LOG(INFO) << "Entry " << entry_index << ": " << entry_name.begin() << " - " << entry_size;
    }

    allocator->DeallocateObject(reader);
    reader = nullptr;

    allocator->DeallocateContainer(buffer, buffer_size);
    buffer = nullptr;

    buffer_size = 0;
}

void DisplayDetails(FAllocator* allocator, FFactory* factory, const std::string& filename) {
    DisplayDetails(allocator, factory, filename.c_str());
}

int main(int argument_count, char** arguments) {
    auto log_worker = std::unique_ptr<LogWorker> {LogWorker::createLogWorker()};

    log_worker->addDefaultLogger("group_test", ".");
    log_worker->addSink(std::make_unique<FConsoleSink>(), &FConsoleSink::ReceiveLogMessage);

    initializeLogging(log_worker.get());

    LOG(INFO) << "Duke Nukem 3D Group Tester";

    auto run_files_error = std::string {""};
    auto run_files       = std::unique_ptr<Runfiles> {Runfiles::Create(arguments[0], &run_files_error)};

    CHECK(run_files != nullptr) << "Failed to initialize Bazel run-files : " << run_files_error;

    auto allocator = GetSystemAllocator();
    auto factory   = GetFactory();

    DisplayDetails(allocator, factory, run_files->Rlocation("game_tools/data/duke_nukem_3d_megaton/master.grp"));
    DisplayDetails(allocator, factory, run_files->Rlocation("game_tools/data/duke_nukem_3d_megaton/caribbean_lifes_a_beach.grp"));
    DisplayDetails(allocator, factory, run_files->Rlocation("game_tools/data/duke_nukem_3d_megaton/duke_it_out_in_dc.grp"));
    DisplayDetails(allocator, factory, run_files->Rlocation("game_tools/data/duke_nukem_3d_megaton/nuclear_winter.grp"));

    return 0;
}
