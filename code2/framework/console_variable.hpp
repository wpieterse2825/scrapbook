#pragma once

class flConsoleVariableSystem {
  public:
    virtual void Start() = 0;
    virtual void Stop()  = 0;
    virtual void Frame() = 0;
};

extern flConsoleVariableSystem* console_variable_system;
