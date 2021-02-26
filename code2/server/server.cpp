#include "server/server.hpp"

class flServerSystemLocal : public flServerSystem {
  public:
    virtual void Start() override;
    virtual void Stop() override;
    virtual void Frame() override;
};

flServerSystemLocal server_system_local;

flServerSystem* server_system = &server_system_local;

void flServerSystemLocal::Start() {
}

void flServerSystemLocal::Stop() {
}

void flServerSystemLocal::Frame() {
}
