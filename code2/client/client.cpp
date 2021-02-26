#include "client/client.hpp"

#include "video/video.hpp"
#include "audio/audio.hpp"

class flClientSystemLocal : public flClientSystem {
  public:
    virtual void Start() override;
    virtual void Stop() override;
    virtual void Frame() override;
};

flClientSystemLocal client_system_local;

flClientSystem* client_system = &client_system_local;

void flClientSystemLocal::Start() {
    video_system->Start();
    audio_system->Start();
}

void flClientSystemLocal::Stop() {
    audio_system->Stop();
    video_system->Stop();
}

void flClientSystemLocal::Frame() {
    video_system->Frame();
    audio_system->Frame();
}
