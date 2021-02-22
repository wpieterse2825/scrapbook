// SPDX-License-Identifier: GPL-3.0

#include "g3log/g3log.hpp"
#include "g3log/logworker.hpp"

#include "tools/cpp/runfiles/runfiles.h"

#include "foundation/console_sink.hpp"
#include "foundation/utilities.hpp"
#include "foundation/allocator.hpp"

#include "games/doom_1/factory.hpp"

#include "games/doom_1/wad/signature.hpp"
#include "games/doom_1/wad/utilities.hpp"

using namespace g3;

using namespace bazel::tools::cpp::runfiles;

using namespace wpieterse2825::game_tools;

using namespace wpieterse2825::game_tools::games::doom_1;

using namespace wpieterse2825::game_tools::games::doom_1::wad;

namespace wpieterse2825::game_tools::tools::doom {
    void DisplayDetails(FAllocator* allocator, FFactory* factory, const char* filename) {
        LOG(INFO) << "Processing " << filename;

        auto buffer_size = size_t {0};
        auto buffer      = ReadCompleteFile(allocator, filename, &buffer_size);
        auto archive     = FMemoryArchiveReader {buffer, buffer_size};
        auto reader      = factory->CreateWADReader(allocator, archive);

        if (reader->Signature() == ESignature::Base) {
            LOG(INFO) << "Signature is Base";
        } else if (reader->Signature() == ESignature::Extension) {
            LOG(INFO) << "Signature is Extension";
        } else {
            LOG(INFO) << "Signature is Unknown";
        }

        auto entries = reader->EntryCount();
        for (auto entry_index = uint32_t {0}; entry_index < entries; entry_index++) {
            auto entry_name = reader->IndexName(entry_index);
            auto entry_size = reader->IndexSize(entry_index);

            LOG(INFO) << "Entry " << entry_index << ": " << NameToString(entry_name).begin() << " - " << entry_size;
        }

        allocator->DeallocateObject(reader);
        reader = nullptr;

        allocator->DeallocateContainer<uint8_t>(buffer, buffer_size);
        buffer = nullptr;

        buffer_size = 0;
    }

    void DisplayDetails(FAllocator* allocator, FFactory* factory, const std::string& filename) {
        DisplayDetails(allocator, factory, filename.c_str());
    }
} // namespace wpieterse2825::game_tools::tools::doom

int main(int argument_count, char** arguments) {
    auto log_worker = std::unique_ptr<LogWorker> {LogWorker::createLogWorker()};

    log_worker->addDefaultLogger("wad_test", ".");
    log_worker->addSink(std::make_unique<FConsoleSink>(), &FConsoleSink::ReceiveLogMessage);

    initializeLogging(log_worker.get());

    LOG(INFO) << "DOOM WAD Tester";

    auto run_files_error = std::string {""};
    auto run_files       = std::unique_ptr<Runfiles> {Runfiles::Create(arguments[0], &run_files_error)};

    CHECK(run_files != nullptr) << "Failed to initialize Bazel run-files : " << run_files_error;

    auto allocator = GetSystemAllocator();
    auto factory   = GetFactory();

    tools::doom::DisplayDetails(allocator, factory, run_files->Rlocation("game_tools/data/doom_1_ultimate/master.wad"));
    tools::doom::DisplayDetails(allocator, factory, run_files->Rlocation("game_tools/data/doom_1_bfg/master.wad"));
    tools::doom::DisplayDetails(allocator, factory, run_files->Rlocation("game_tools/data/doom_1_eternal/master.wad"));
    tools::doom::DisplayDetails(allocator, factory, run_files->Rlocation("game_tools/data/doom_1_unity/master.wad"));
    tools::doom::DisplayDetails(allocator, factory, run_files->Rlocation("game_tools/data/doom_1_unity/extras.wad"));

    return 0;
}
