#pragma once

class flClientManager {
  public:
    virtual ~flClientManager() {
    }

    virtual void Start() = 0;
    virtual void Stop()  = 0;
    virtual void Frame() = 0;
};

extern flClientManager* client_manager;
