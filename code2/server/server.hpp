#pragma once

class flServerSystem {
  public:
    virtual void Start() = 0;
    virtual void Stop()  = 0;
    virtual void Frame() = 0;
};

extern flServerSystem* server_system;
