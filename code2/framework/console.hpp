#pragma once

class flConsoleSystem {
  public:
    virtual void Start() = 0;
    virtual void Stop()  = 0;
    virtual void Frame() = 0;
};

extern flConsoleSystem* console_system;
