#include "foundation/stack_record.hpp"

#include "audio/audio.hpp"

class flAudioManagerLocal final : public flAudioManager {
  public:
    flAudioManagerLocal();
    virtual ~flAudioManagerLocal();

    virtual void Start() override;
    virtual void Stop() override;
    virtual void Frame() override;
};

static flAudioManagerLocal audio_manager_local;

flAudioManager* audio_manager = &audio_manager_local;

flAudioManagerLocal::flAudioManagerLocal() {
    GENERATE_STACK_RECORD();
}

flAudioManagerLocal::~flAudioManagerLocal() {
    GENERATE_STACK_RECORD();
}

void flAudioManagerLocal::Start() {
    GENERATE_STACK_RECORD();
}

void flAudioManagerLocal::Stop() {
    GENERATE_STACK_RECORD();
}

void flAudioManagerLocal::Frame() {
    GENERATE_STACK_RECORD();
}
