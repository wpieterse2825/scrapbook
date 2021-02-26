#include "foundation/stack_record.hpp"

#include "framework/console_variable.hpp"

class flConsoleVariableManagerLocal final : public flConsoleVariableManager {
  public:
    flConsoleVariableManagerLocal();
    virtual ~flConsoleVariableManagerLocal();

    virtual void Start() override;
    virtual void Stop() override;
    virtual void Frame() override;
};

static flConsoleVariableManagerLocal console_variable_manager_local;

flConsoleVariableManager* console_variable_manager = &console_variable_manager_local;

flConsoleVariableManagerLocal::flConsoleVariableManagerLocal() {
    GENERATE_STACK_RECORD();
}

flConsoleVariableManagerLocal::~flConsoleVariableManagerLocal() {
    GENERATE_STACK_RECORD();
}

void flConsoleVariableManagerLocal::Start() {
    GENERATE_STACK_RECORD();
}

void flConsoleVariableManagerLocal::Stop() {
    GENERATE_STACK_RECORD();
}

void flConsoleVariableManagerLocal::Frame() {
    GENERATE_STACK_RECORD();
}
