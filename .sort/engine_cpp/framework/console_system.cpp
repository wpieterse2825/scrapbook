#include <stdio.h>

#include "foundation/stack_record.hpp"

#include "framework/console_system.hpp"

class flConsoleSystemManagerLocal final : public flConsoleSystemManager {
  public:
    flConsoleSystemManagerLocal();
    virtual ~flConsoleSystemManagerLocal();

    virtual void Start() override;
    virtual void Stop() override;
    virtual void Frame() override;

    virtual void Print(const char* message) override;
};

static flConsoleSystemManagerLocal console_system_manager_local;

flConsoleSystemManager* console_system_manager = &console_system_manager_local;

flConsoleSystemManagerLocal::flConsoleSystemManagerLocal() {
    GENERATE_STACK_RECORD();
}

flConsoleSystemManagerLocal::~flConsoleSystemManagerLocal() {
    GENERATE_STACK_RECORD();
}

void flConsoleSystemManagerLocal::Start() {
    GENERATE_STACK_RECORD();
}

void flConsoleSystemManagerLocal::Stop() {
    GENERATE_STACK_RECORD();
}

void flConsoleSystemManagerLocal::Frame() {
    GENERATE_STACK_RECORD();
}

void flConsoleSystemManagerLocal::Print(const char* message) {
    GENERATE_STACK_RECORD();

    printf("%s", message);
}
