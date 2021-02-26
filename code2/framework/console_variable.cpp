#include "framework/console_variable.hpp"

class flConsoleVariableSystemLocal : public flConsoleVariableSystem {
  public:
    virtual void Start() override;
    virtual void Stop() override;
    virtual void Frame() override;
};

flConsoleVariableSystemLocal console_variable_system_local;

flConsoleVariableSystem* console_variable_system = &console_variable_system_local;

void flConsoleVariableSystemLocal::Start() {
}

void flConsoleVariableSystemLocal::Stop() {
}

void flConsoleVariableSystemLocal::Frame() {
}
