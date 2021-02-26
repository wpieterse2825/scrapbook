#pragma once

class flVideoSystem {
  public:
    virtual void Start() = 0;
    virtual void Stop()  = 0;
    virtual void Frame() = 0;
};

extern flVideoSystem* video_system;
