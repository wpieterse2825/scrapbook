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
#define LOG_LEVEL_ERROR       0x03

#define LARGE_STRING_MAXIMUM 16 * 1024

#define PARSE_BUFFER_MAXIMUM 16 * 1024

#define COMMAND_ARGUMENT_MAXIMUM 64
#define COMMAND_LINE_MAXIMUM     1024

typedef enum memory_tag_s
{
    MEMORY_TAG_DEFAULT = 0,
    MEMORY_TAG_STRING,
} memory_tag_e;

typedef struct command_arguments_s {
    size_t argument_count;
    char   arguments[COMMAND_ARGUMENT_MAXIMUM][COMMAND_LINE_MAXIMUM];
} command_arguments_t;

typedef void (*command_callback)(command_arguments_t command_arguments);

void Common_Error(const char* message, ...);
void Common_Log(uint8_t log_levevel, const char* message, ...);

void* Memory_SystemAllocate(size_t length, memory_tag_e tag);
void  Memory_SystemFree(void* buffer);

char*   String_Allocate(size_t string_length);
void    String_Free(char* input_string);
size_t  String_Length(const char* input_string);
bool    String_Compare(const char* lhs, const char* rhs);
bool    String_CompareSize(const char* lhs, const char* rhs, size_t compare_length);
void    String_Copy(const char* source, char* destination);
void    String_CopySize(const char* source, char* destination, size_t destination_length);
char*   String_Clone(const char* input_string);
void    String_Print(char* buffer, size_t buffer_length, const char* format, ...);
int64_t String_ToInteger(const char* source);
char*   String_FromInteger(int64_t value);

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
