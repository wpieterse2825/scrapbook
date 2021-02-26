#include "foundation/stack_record.hpp"

#include "video/video.hpp"

class flVideoManagerLocal final : public flVideoManager {
  public:
    flVideoManagerLocal();
    virtual ~flVideoManagerLocal();

    virtual void Start() override;
    virtual void Stop() override;
    virtual void Frame() override;
};

static flVideoManagerLocal video_manager_local;

flVideoManager* video_manager = &video_manager_local;

flVideoManagerLocal::flVideoManagerLocal() {
    GENERATE_STACK_RECORD();
}

flVideoManagerLocal::~flVideoManagerLocal() {
    GENERATE_STACK_RECORD();
}

void flVideoManagerLocal::Start() {
    GENERATE_STACK_RECORD();
}

void flVideoManagerLocal::Stop() {
    GENERATE_STACK_RECORD();
}

void flVideoManagerLocal::Frame() {
    GENERATE_STACK_RECORD();
}
