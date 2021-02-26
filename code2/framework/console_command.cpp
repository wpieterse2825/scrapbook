#include "framework/console_command.hpp"

class flConsoleCommandSystemLocal : public flConsoleCommandSystem {
  public:
    virtual void Start() override;
    virtual void Stop() override;
    virtual void Frame() override;
};

flConsoleCommandSystemLocal console_command_system_local;

flConsoleCommandSystem* console_command_system = &console_command_system_local;

void flConsoleCommandSystemLocal::Start() {
}

void flConsoleCommandSystemLocal::Stop() {
}

void flConsoleCommandSystemLocal::Frame() {
}
