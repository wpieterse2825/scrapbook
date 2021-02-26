#pragma once

class flClientSystem {
  public:
    virtual void Start() = 0;
    virtual void Stop()  = 0;
    virtual void Frame() = 0;
};

extern flClientSystem* client_system;
