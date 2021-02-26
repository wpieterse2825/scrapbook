#include "framework/console.hpp"

class flConsoleSystemLocal : public flConsoleSystem {
  public:
    virtual void Start() override;
    virtual void Stop() override;
    virtual void Frame() override;
};

flConsoleSystemLocal console_system_local;

flConsoleSystem* console_system = &console_system_local;

void flConsoleSystemLocal::Start() {
}

void flConsoleSystemLocal::Stop() {
}

void flConsoleSystemLocal::Frame() {
}
