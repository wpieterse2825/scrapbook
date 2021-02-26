#include "foundation/stack_record.hpp"

#include "framework/common.hpp"

#include "framework/console_game.hpp"

class flConsoleGameManagerLocal final : public flConsoleGameManager {
  public:
    flConsoleGameManagerLocal();
    virtual ~flConsoleGameManagerLocal();

    virtual void Start() override;
    virtual void Stop() override;
    virtual void Frame() override;

    virtual void Print(const char* message) override;
};

static flConsoleGameManagerLocal console_game_manager_local;

flConsoleGameManager* console_game_manager = &console_game_manager_local;

flConsoleGameManagerLocal::flConsoleGameManagerLocal() {
    GENERATE_STACK_RECORD();
}

flConsoleGameManagerLocal::~flConsoleGameManagerLocal() {
    GENERATE_STACK_RECORD();
}

void flConsoleGameManagerLocal::Start() {
    GENERATE_STACK_RECORD();
}

void flConsoleGameManagerLocal::Stop() {
    GENERATE_STACK_RECORD();
}

void flConsoleGameManagerLocal::Frame() {
    GENERATE_STACK_RECORD();
}

void flConsoleGameManagerLocal::Print(const char* message) {
    GENERATE_STACK_RECORD();
}
