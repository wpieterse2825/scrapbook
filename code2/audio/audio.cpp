#include "audio/audio.hpp"

class flAudioSystemLocal : public flAudioSystem {
  public:
    virtual void Start() override;
    virtual void Stop() override;
    virtual void Frame() override;
};

flAudioSystemLocal audio_system_local;

flAudioSystem* audio_system = &audio_system_local;

void flAudioSystemLocal::Start() {
}

void flAudioSystemLocal::Stop() {
}

void flAudioSystemLocal::Frame() {
}
