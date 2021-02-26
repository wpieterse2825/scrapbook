#pragma once

class flServerManager {
  public:
    virtual ~flServerManager() {
    }

    virtual void Start() = 0;
    virtual void Stop()  = 0;
    virtual void Frame() = 0;
};

extern flServerManager* server_manager;
