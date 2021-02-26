#include "foundation/stack_record.hpp"

#include "server/server.hpp"

class flServerManagerLocal final : public flServerManager {
  public:
    flServerManagerLocal();
    virtual ~flServerManagerLocal();

    virtual void Start() override;
    virtual void Stop() override;
    virtual void Frame() override;
};

static flServerManagerLocal server_manager_local;

flServerManager* server_manager = &server_manager_local;

flServerManagerLocal::flServerManagerLocal() {
    GENERATE_STACK_RECORD();
}

flServerManagerLocal::~flServerManagerLocal() {
    GENERATE_STACK_RECORD();
}

void flServerManagerLocal::Start() {
    GENERATE_STACK_RECORD();
}

void flServerManagerLocal::Stop() {
    GENERATE_STACK_RECORD();
}

void flServerManagerLocal::Frame() {
    GENERATE_STACK_RECORD();
}
