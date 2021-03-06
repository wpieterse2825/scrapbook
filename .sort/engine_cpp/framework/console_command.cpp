#include "foundation/stack_record.hpp"

#include "framework/console_command.hpp"

class flConsoleCommandManagerLocal final : public flConsoleCommandManager {
  public:
    flConsoleCommandManagerLocal();
    virtual ~flConsoleCommandManagerLocal();

    virtual void Start() override;
    virtual void Stop() override;
    virtual void Frame() override;
};

static flConsoleCommandManagerLocal console_command_manager_local;

flConsoleCommandManager* console_command_manager = &console_command_manager_local;

flConsoleCommandManagerLocal::flConsoleCommandManagerLocal() {
    GENERATE_STACK_RECORD();
}

flConsoleCommandManagerLocal::~flConsoleCommandManagerLocal() {
    GENERATE_STACK_RECORD();
}

void flConsoleCommandManagerLocal::Start() {
    GENERATE_STACK_RECORD();
}

void flConsoleCommandManagerLocal::Stop() {
    GENERATE_STACK_RECORD();
}

void flConsoleCommandManagerLocal::Frame() {
    GENERATE_STACK_RECORD();
}
