#include "video/video.hpp"

class flVideoSystemLocal : public flVideoSystem {
  public:
    virtual void Start() override;
    virtual void Stop() override;
    virtual void Frame() override;
};

flVideoSystemLocal video_system_local;

flVideoSystem* video_system = &video_system_local;

void flVideoSystemLocal::Start() {
}

void flVideoSystemLocal::Stop() {
}

void flVideoSystemLocal::Frame() {
}
