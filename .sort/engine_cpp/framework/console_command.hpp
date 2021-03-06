#pragma once

class flConsoleCommandManager {
  public:
    virtual ~flConsoleCommandManager() {
    }

    virtual void Start() = 0;
    virtual void Stop()  = 0;
    virtual void Frame() = 0;
};

extern flConsoleCommandManager* console_command_manager;
