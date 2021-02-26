#pragma once

class flConsoleGameManager {
  public:
    virtual ~flConsoleGameManager() {
    }

    virtual void Start() = 0;
    virtual void Stop()  = 0;
    virtual void Frame() = 0;

    virtual void Print(const char* message) = 0;
};

extern flConsoleGameManager* console_game_manager;
