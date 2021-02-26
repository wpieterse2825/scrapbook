#pragma once

class flConsoleSystemManager {
  public:
    virtual ~flConsoleSystemManager() {
    }

    virtual void Start() = 0;
    virtual void Stop()  = 0;
    virtual void Frame() = 0;

    virtual void Print(const char* message) = 0;
};

extern flConsoleSystemManager* console_system_manager;
