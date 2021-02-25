#include "common/com_public.h"
#include "common/com_local.h"

#define CONSOLE_BUFFER_MAXIMUM 16 * 1024
#define CONSOLE_LINE_MAXIMUM   1024

uint8_t  console_backing_buffer[CONSOLE_BUFFER_MAXIMUM] = {0};
uint8_t* console_buffer                                 = NULL;
size_t   console_maximum_usage                          = 0;
size_t   console_current_usage                          = 0;

static void Console_ExecuteBuffer();
static void Console_ExecuteLine(const char* line);

void Console_Start() {
    memset(console_backing_buffer, 0, CONSOLE_BUFFER_MAXIMUM);

    console_buffer        = console_backing_buffer;
    console_maximum_usage = CONSOLE_BUFFER_MAXIMUM;
    console_current_usage = 0;
}

void Console_Stop() {
    console_current_usage = 0;
    console_maximum_usage = 0;
    console_buffer        = NULL;

    memset(console_backing_buffer, 0, CONSOLE_BUFFER_MAXIMUM);
}

void Console_Frame() {
    Console_ExecuteBuffer();
}

void Console_AddText(const char* command) {
    assert(command != NULL);

    size_t command_length = strlen(command);
    size_t final_length   = console_current_usage + command_length;

    if (final_length > console_maximum_usage) {
        Common_Log(LOG_LEVEL_WARNING, "Console buffer working_buffer overflowed.\n");

        return;
    }

    memcpy(&console_buffer[console_current_usage], command, command_length);
    console_current_usage += command_length;
}

void Console_AddLine(const char* command) {
    char command_line[CONSOLE_LINE_MAXIMUM] = {0};

    assert(command != NULL);

    snprintf(command_line, CONSOLE_LINE_MAXIMUM, "%s\n", command);

    Console_AddText(command_line);
}

static void Console_ExecuteBuffer() {
    int64_t index                              = 0;
    char*   working_buffer                     = NULL;
    char    working_line[CONSOLE_LINE_MAXIMUM] = {0};
    int64_t quotes                             = 0;

    while (console_current_usage > 0) {
        working_buffer = console_buffer;

        quotes = 0;
        for (index = 0; index < console_current_usage; index++) {
            if (working_buffer[index] == '"') {
                quotes++;
            }

            if (!(quotes & 1) && working_buffer[index] == ';') {
                break;
            }

            if (working_buffer[index] == '\n' || working_buffer[index] == '\r') {
                break;
            }
        }

        if (index >= (CONSOLE_LINE_MAXIMUM - 1)) {
            index = CONSOLE_LINE_MAXIMUM - 1;
        }

        memcpy(working_line, working_buffer, index);
        working_line[index] = 0;

        if (index == console_current_usage) {
            console_current_usage = 0;
        } else {
            index++;
            console_current_usage -= index;
            memmove(working_buffer, working_buffer + index, console_current_usage);
        }

        Console_ExecuteLine(working_line);
    }
}

static void Console_ExecuteLine(const char* line) {
    assert(line != NULL);

    Command_Call(line);
}
