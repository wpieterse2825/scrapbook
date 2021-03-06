#pragma once

class flConsoleVariableManager {
  public:
    virtual ~flConsoleVariableManager() {
    }

    virtual void Start() = 0;
    virtual void Stop()  = 0;
    virtual void Frame() = 0;
};

extern flConsoleVariableManager* console_variable_manager;
