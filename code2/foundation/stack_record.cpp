#include "foundation/stack_record.hpp"

static int64_t        total_stack_records               = 0;
static flStackRecord* stack_records[StackRecordMaximum] = {nullptr};

flStackRecord::flStackRecord(const char* function_name)
  : _function_name {function_name} {
    stack_records[total_stack_records] = this;
    total_stack_records++;
}

flStackRecord::~flStackRecord() {
    total_stack_records--;
}

const char* flStackRecord::GetFunctionName() const {
    return _function_name;
}

int64_t StackRecord_Total() {
    return total_stack_records;
}

const char* StackRecord_At(int64_t index) {
    flStackRecord* record = stack_records[index];

    return record->GetFunctionName();
}
