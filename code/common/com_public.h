#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
#include <assert.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define LOG_LEVEL_DEVELOPER   0x00
#define LOG_LEVEL_INFORMATION 0x01
#define LOG_LEVEL_WARNING     0x02

#define COMMAND_ARGUMENTS_COUNT_MAXIMUM 16
#define COMMAND_ARGUMENTS_LINE_MAXIMUM  256

typedef struct command_arguments_s {
    size_t argument_count;
    char   arguments[COMMAND_ARGUMENTS_COUNT_MAXIMUM][COMMAND_ARGUMENTS_LINE_MAXIMUM];
} command_arguments_t;

typedef void (*command_callback)(command_arguments_t command_arguments);

void Common_Error(const char* message, ...);
void Common_Log(uint8_t log_levevel, const char* message, ...);

char* String_Allocate(size_t string_length);
void  String_Free(char* input_string);
char* String_Copy(const char* input_string);
bool  String_Compare(const char* lhs, const char* rhs);

void ConsoleBuffer_AddText(const char* command);
void ConsoleBuffer_AddLine(const char* command);

int64_t     Variable_Register(const char* key, const char* value, uint64_t flags);
void        Variable_Unregister(int64_t variable_handle);
void        Variable_Reset(int64_t variable_handle);
const char* Variable_GetString(int64_t variable_handle);
void        Variable_SetString(int64_t variable_handle, const char* value);
int64_t     Variable_GetInteger(int64_t variable_handle);
void        Variable_SetInteger(int64_t variable_handle, int64_t value);
bool        Variable_IsModified(int64_t variable_handle);
int64_t     Variable_ModificationCount(int64_t variable_handle);
void        Variable_ClearModified(int64_t variable_handle);

int64_t Command_Register(const char* name, command_callback callback);
void    Command_Unregister(int64_t command_handle);
void    Command_Call(const char* line);
