#include <stdint.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "foundation/exception.hpp"
#include "foundation/stack_record.hpp"

#include "framework/console.hpp"
#include "framework/console_variable.hpp"
#include "framework/console_command.hpp"

#include "server/server.hpp"
#include "client/client.hpp"

#include "framework/common.hpp"

constexpr uint64_t ExceptionMessageSize = 16 * 1024;
constexpr uint64_t PrintMessageSize     = 16 * 1024;

class flCommonLocal final : public flCommon {
  public:
    flCommonLocal();
    virtual ~flCommonLocal();

    virtual void Start() override;
    virtual void Stop() override;
    virtual bool Frame() override;

    virtual void Error(const char* message, ...) override;
    virtual void Print(const char* message, ...) override;

  private:
    void HandleError(const flException& exception);

  private:
    bool _error_entered;
    char _error_message[ExceptionMessageSize];
    char _error_stack[ExceptionMessageSize];
};

static flCommonLocal common_local;

flCommon* common = &common_local;

flCommonLocal::flCommonLocal()
  : _error_entered {false}
  , _error_message {0}
  , _error_stack {0} {
    GENERATE_STACK_RECORD();
}

flCommonLocal::~flCommonLocal() {
    GENERATE_STACK_RECORD();
}

void flCommonLocal::Start() {
    GENERATE_STACK_RECORD();

    try {
        console_manager->Start();
        console_variable_manager->Start();
        console_command_manager->Start();

        server_manager->Start();
        client_manager->Start();
    } catch (flException& exception) {
        HandleError(exception);
    }
}

void flCommonLocal::Stop() {
    GENERATE_STACK_RECORD();

    try {
        client_manager->Stop();
        server_manager->Stop();

        console_command_manager->Stop();
        console_variable_manager->Stop();
        console_manager->Stop();
    } catch (flException& exception) {
        HandleError(exception);
    }
}

bool flCommonLocal::Frame() {
    GENERATE_STACK_RECORD();

    try {
        console_manager->Frame();
        console_variable_manager->Frame();
        console_command_manager->Frame();

        server_manager->Frame();
        client_manager->Frame();
    } catch (flException& exception) {
        HandleError(exception);
    }

    return false;
}

void flCommonLocal::Error(const char* message, ...) {
    va_list argument_list = {};
    int64_t stack_records = 0;

    if (_error_entered == true) {
        Print("FATAL: Recursive error detected, force quitting.\n");

        exit(1);
    }

    _error_entered = true;

    va_start(argument_list, message);
    vsprintf(_error_message, message, argument_list);
    va_end(argument_list);

    stack_records = StackRecord_Total();

    for (int64_t index = stack_records - 1; index >= 0; index--) {
        const char* stack_name = StackRecord_At(index);

        strcat(_error_stack, " * ");
        strcat(_error_stack, stack_name);

        if (index != 0) {
            strcat(_error_stack, "\n");
        }
    }

    throw flException(_error_message, _error_stack);
}

void flCommonLocal::Print(const char* message, ...) {
    GENERATE_STACK_RECORD();

    char    formatted_message[PrintMessageSize] = {0};
    va_list argument_list                       = {};

    va_start(argument_list, message);
    vsnprintf(formatted_message, PrintMessageSize, message, argument_list);
    va_end(argument_list);

    console_manager->Print(formatted_message);
}

void flCommonLocal::HandleError(const flException& exception) {
    const char* description = exception.GetDescription();
    const char* stack_trace = exception.GetStackTrace();

    Print("ERROR: %s\n", description);
    Print("STACK:\n");
    Print("%s\n", stack_trace);
}
