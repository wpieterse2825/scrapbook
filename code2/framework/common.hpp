#pragma once

class flCommon {
  public:
    virtual ~flCommon() {
    }

    virtual void Start() = 0;
    virtual void Stop()  = 0;
    virtual bool Frame() = 0;

    virtual void Error(const char* message, ...) = 0;
    virtual void Print(const char* message, ...) = 0;
};

extern flCommon* common;
