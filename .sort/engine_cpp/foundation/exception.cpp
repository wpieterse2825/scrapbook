#include "foundation/exception.hpp"

flException::flException(const char* description, const char* stack_trace)
  : _description {description}
  , _stack_trace {stack_trace} {
}

flException::~flException() {
}

const char* flException::GetDescription() const {
    return _description;
}

const char* flException::GetStackTrace() const {
    return _stack_trace;
}
