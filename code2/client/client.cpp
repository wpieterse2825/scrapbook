#include "foundation/stack_record.hpp"

#include "video/video.hpp"
#include "audio/audio.hpp"

#include "client/client.hpp"

class flClientManagerLocal final : public flClientManager {
  public:
    flClientManagerLocal();
    virtual ~flClientManagerLocal();

    virtual void Start() override;
    virtual void Stop() override;
    virtual void Frame() override;
};

static flClientManagerLocal client_manager_local;

flClientManager* client_manager = &client_manager_local;

flClientManagerLocal::flClientManagerLocal() {
    GENERATE_STACK_RECORD();
}

flClientManagerLocal::~flClientManagerLocal() {
    GENERATE_STACK_RECORD();
}

void flClientManagerLocal::Start() {
    GENERATE_STACK_RECORD();

    video_manager->Start();
    audio_manager->Start();
}

void flClientManagerLocal::Stop() {
    GENERATE_STACK_RECORD();

    audio_manager->Stop();
    video_manager->Stop();
}

void flClientManagerLocal::Frame() {
    GENERATE_STACK_RECORD();

    video_manager->Frame();
    audio_manager->Frame();
}
