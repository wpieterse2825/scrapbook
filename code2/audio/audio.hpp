#pragma once

class flAudioSystem {
  public:
    virtual void Start() = 0;
    virtual void Stop()  = 0;
    virtual void Frame() = 0;
};

extern flAudioSystem* audio_system;
