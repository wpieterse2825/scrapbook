#define __STDC_WANT_LIB_EXT1__ 1

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
#include <assert.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define BIT(index) (1 << index)

#define ENGINE_NAME    "Folklore"
#define ENGINE_VERSION 1

#define GAME_NAME    "Folklore"
#define GAME_VERSION 1

#define PRINT_LEVEL_DEVELOPER   0x00
#define PRINT_LEVEL_INFORMATION 0x01
#define PRINT_LEVEL_WARNING     0x02
#define PRINT_LEVEL_ERROR       0x03

#define LARGE_STRING_MAXIMUM 16 * 1024
#define PARSE_BUFFER_MAXIMUM 16 * 1024

#define VARIABLE_FLAG_PRODUCTION BIT(0)
#define VARIABLE_FLAG_STATIC     BIT(1)
#define VARIABLE_FLAG_READ_ONLY  BIT(2)
#define VARIABLE_FLAG_ARCHIVE    BIT(3)
#define VARIABLE_FLAG_SYSTEM     BIT(4)
#define VARIABLE_FLAG_RENDERER   BIT(5)
#define VARIABLE_FLAG_SOUND      BIT(6)
#define VARIABLE_FLAG_INPUT      BIT(7)
#define VARIABLE_FLAG_NETWORK    BIT(8)
#define VARIABLE_FLAG_TOOL       BIT(9)
#define VARIABLE_FLAG_GAME       BIT(10)
#define VARIABLE_FLAG_CHEAT      BIT(31)

#define COMMAND_FLAG_PRODUCTION BIT(0)
#define COMMAND_FLAG_SYSTEM     BIT(1)
#define COMMAND_FLAG_RENDERER   BIT(2)
#define COMMAND_FLAG_SOUND      BIT(3)
#define COMMAND_FLAG_INPUT      BIT(4)
#define COMMAND_FLAG_NETWORK    BIT(5)
#define COMMAND_FLAG_TOOL       BIT(6)
#define COMMAND_FLAG_GAME       BIT(7)
#define COMMAND_FLAG_CHEAT      BIT(31)

#define COMMAND_ARGUMENT_MAXIMUM 64
#define COMMAND_LINE_MAXIMUM     1024

typedef enum memory_tag_s
{
    MEMORY_TAG_DEFAULT = 0,
    MEMORY_TAG_STRING,
    MEMORY_TAG_RENDERER,
} memory_tag_e;

typedef struct command_arguments_s {
    size_t argument_count;
    char   arguments[COMMAND_ARGUMENT_MAXIMUM][COMMAND_LINE_MAXIMUM];
} command_arguments_t;

typedef void (*command_callback)(command_arguments_t command_arguments);

typedef struct common_export_log_s {
    void (*Error)(const char* message, ...);
    void (*Print)(uint8_t log_levevel, const char* message, ...);
} common_export_log_t;

typedef struct common_export_memory_system_s {
    void* (*Allocate)(size_t length, memory_tag_e tag);
    void (*Free)(void* buffer);
} common_export_memory_system_t;

typedef struct common_export_string_s {
    char* (*Allocate)(size_t string_length);
    void (*Free)(char* input_string);
    size_t (*Length)(const char* input_string);
    bool (*Compare)(const char* lhs, const char* rhs, size_t compare_length);
    void (*Copy)(const char* source, char* destination, size_t destination_length);
    char* (*Clone)(const char* input_string);
    void (*Print)(char* buffer, size_t buffer_length, const char* format, ...);
    int64_t (*ToInteger)(const char* source);
    char* (*FromInteger)(int64_t value);
} common_export_string_t;

typedef struct common_export_console_buffer_s {
    void (*AddText)(const char* command);
    void (*AddLine)(const char* command);
} common_export_console_buffer_t;

typedef struct common_export_variable_s {
    int64_t (*Register)(const char* key, const char* value, uint64_t flags);
    void (*Unregister)(int64_t variable_handle);
    void (*Reset)(int64_t variable_handle);
    const char* (*GetString)(int64_t variable_handle);
    void (*SetString)(int64_t variable_handle, const char* value);
    int64_t (*GetInteger)(int64_t variable_handle);
    void (*SetInteger)(int64_t variable_handle, int64_t value);
    bool (*IsModified)(int64_t variable_handle);
    int64_t (*ModificationCount)(int64_t variable_handle);
    void (*ClearModified)(int64_t variable_handle);
} common_export_variable_t;

typedef struct common_export_command_s {
    int64_t (*Register)(const char* name, command_callback callback, uint64_t flags);
    void (*Unregister)(int64_t command_handle);
} common_export_command_t;

typedef struct common_export_s {
    common_export_log_t*            log;
    common_export_memory_system_t*  memory_system;
    common_export_string_t*         string;
    common_export_console_buffer_t* console_buffer;
    common_export_variable_t*       variable;
    common_export_command_t*        command;
} common_export_t;
