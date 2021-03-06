#pragma once

class flAudioManager {
  public:
    virtual ~flAudioManager() {
    }

    virtual void Start() = 0;
    virtual void Stop()  = 0;
    virtual void Frame() = 0;
};

extern flAudioManager* audio_manager;
