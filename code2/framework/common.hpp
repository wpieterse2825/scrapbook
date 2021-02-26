#pragma once

class flCommon {
  public:
    virtual void Start() = 0;
    virtual void Stop()  = 0;
    virtual bool Frame() = 0;
};

extern flCommon* common;
