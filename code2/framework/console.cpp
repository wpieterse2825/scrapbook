#include "foundation/stack_record.hpp"

#include "framework/console_system.hpp"
#include "framework/console_game.hpp"

#include "framework/console.hpp"

class flConsoleManagerLocal final : public flConsoleManager {
  public:
    flConsoleManagerLocal();
    virtual ~flConsoleManagerLocal();

    virtual void Start() override;
    virtual void Stop() override;
    virtual void Frame() override;

    virtual void Print(const char* message) override;
};

static flConsoleManagerLocal console_manager_local;

flConsoleManager* console_manager = &console_manager_local;

flConsoleManagerLocal::flConsoleManagerLocal() {
    GENERATE_STACK_RECORD();
}

flConsoleManagerLocal::~flConsoleManagerLocal() {
    GENERATE_STACK_RECORD();
}

void flConsoleManagerLocal::Start() {
    GENERATE_STACK_RECORD();

    console_system_manager->Start();
    console_game_manager->Start();
}

void flConsoleManagerLocal::Stop() {
    GENERATE_STACK_RECORD();

    console_game_manager->Stop();
    console_system_manager->Stop();
}

void flConsoleManagerLocal::Frame() {
    GENERATE_STACK_RECORD();

    console_system_manager->Frame();
    console_game_manager->Frame();
}

void flConsoleManagerLocal::Print(const char* message) {
    GENERATE_STACK_RECORD();

    console_system_manager->Print(message);
    console_game_manager->Print(message);
}
