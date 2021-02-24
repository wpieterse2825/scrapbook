#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>

void System_Start();
void System_Stop();

void System_Frame();

void System_Error(const char* message, ...);
