#pragma once

class flException final {
  public:
    flException(const char* description, const char* stack_trace);
    ~flException();

    const char* GetDescription() const;
    const char* GetStackTrace() const;

  private:
    const char* _description;
    const char* _stack_trace;
};
