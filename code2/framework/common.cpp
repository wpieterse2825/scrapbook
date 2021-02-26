#include "framework/common.hpp"

#include "framework/console.hpp"
#include "framework/console_variable.hpp"
#include "framework/console_command.hpp"

#include "server/server.hpp"
#include "client/client.hpp"

class flCommonLocal : public flCommon {
  public:
    virtual void Start() override;
    virtual void Stop() override;
    virtual bool Frame() override;
};

flCommonLocal common_local;

flCommon* common = &common_local;

void flCommonLocal::Start() {
    console_system->Start();
    console_variable_system->Start();
    console_command_system->Start();

    server_system->Start();
    client_system->Start();
}

void flCommonLocal::Stop() {
    client_system->Stop();
    server_system->Stop();

    console_command_system->Stop();
    console_variable_system->Stop();
    console_system->Stop();
}

bool flCommonLocal::Frame() {
    console_system->Frame();
    console_variable_system->Frame();
    console_command_system->Frame();

    server_system->Frame();
    client_system->Frame();

    return false;
}
