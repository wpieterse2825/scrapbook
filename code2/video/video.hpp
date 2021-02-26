#pragma once

class flVideoManager {
  public:
    virtual ~flVideoManager() {
    }

    virtual void Start() = 0;
    virtual void Stop()  = 0;
    virtual void Frame() = 0;
};

extern flVideoManager* video_manager;
