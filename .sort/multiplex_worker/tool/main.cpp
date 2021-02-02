#include <stdint.h>
#include <string.h>
#include <immintrin.h>
#include <iostream>

class nmError {
  public:
    nmError(const char* message);

    const char* GetMessage() const;

  private:
    const char* _message;
};

nmError::nmError(const char* message)
  : _message {message} {
}

const char* nmError::GetMessage() const {
    return this->_message;
}

#define FUNCTION_GUARD(function_name)                                                                                                                          \
    nmFunctionGuard _local_guard {                                                                                                                             \
#        function_name                                                                                                                                         \
    }

class nmFunctionGuard {
  public:
    nmFunctionGuard(const char* function_name);
    ~nmFunctionGuard();
};

int64_t     function_stack_depth = 0;
const char* function_stack[256]  = {nullptr};

nmFunctionGuard::nmFunctionGuard(const char* function_name) {
    function_stack[function_stack_depth] = function_name;
    function_stack_depth++;
}

nmFunctionGuard::~nmFunctionGuard() {
    function_stack_depth--;
}

class nmVirtualBase {
  public:
    virtual ~nmVirtualBase() {
    }
};

class nmCommon : public nmVirtualBase {
  public:
    virtual void Start() = 0;
    virtual void Stop()  = 0;

    virtual void Error(const char* message) = 0;
};

class nmCommonLocal : public nmCommon {
  public:
    virtual void Start();
    virtual void Stop();

    virtual void Error(const char* message);
};

nmCommonLocal common_local;
nmCommon*     common = &common_local;

void nmCommonLocal::Start() {
    FUNCTION_GUARD(nmCommonLocal::Start);
}

void nmCommonLocal::Stop() {
    FUNCTION_GUARD(nmCommonLocal::Stop);
}

void nmCommonLocal::Error(const char* message) {
    static char final_message[128 * 1024] = {0};

    strcat(final_message, "ERROR: ");
    strcat(final_message, message);
    strcat(final_message, "\n\nFunction Stack:\n");
    if (function_stack_depth > 0) {
        for (int64_t function_stack_depth_index = (function_stack_depth - 1); function_stack_depth_index >= 0; function_stack_depth_index--) {
            strcat(final_message, " - ");
            strcat(final_message, function_stack[function_stack_depth_index]);
            strcat(final_message, "\n");
        }
    }

    throw nmError(final_message);
}

int main(int argument_count, char** arguments) {
    try {
        FUNCTION_GUARD(main);
        common->Start();
        common->Stop();
    } catch (const nmError& error) {
        if (error.GetMessage() != nullptr) {
            std::cout << error.GetMessage() << std::endl;
        } else {
            std::cout << "Unknown error" << std::endl;
        }
    }

    return 0;
}
