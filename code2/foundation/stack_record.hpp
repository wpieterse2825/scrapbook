#pragma once

#include <stdint.h>

#define GENERATE_STACK_RECORD()                                                                                                            \
    flStackRecord stack_record {                                                                                                           \
        __PRETTY_FUNCTION__                                                                                                                \
    }

constexpr uint64_t StackRecordMaximum = 1024;

class flStackRecord final {
  public:
    flStackRecord(const char* function_name);
    ~flStackRecord();

    const char* GetFunctionName() const;

  private:
    const char* _function_name;
};

int64_t     StackRecord_Total();
const char* StackRecord_At(int64_t index);
