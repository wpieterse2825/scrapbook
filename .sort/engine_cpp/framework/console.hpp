#pragma once

class flConsoleManager {
  public:
    virtual ~flConsoleManager() {
    }

    virtual void Start() = 0;
    virtual void Stop()  = 0;
    virtual void Frame() = 0;

    virtual void Print(const char* message) = 0;
};

extern flConsoleManager* console_manager;
