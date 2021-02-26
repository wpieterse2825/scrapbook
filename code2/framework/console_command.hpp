#pragma once

class flConsoleCommandSystem {
  public:
    virtual void Start() = 0;
    virtual void Stop()  = 0;
    virtual void Frame() = 0;
};

extern flConsoleCommandSystem* console_command_system;
