#include "common/com_public.h"
#include "common/com_local.h"

#define CONSOLEBUFFER_BUFFER_MAXIMUM 16 * 1024
#define CONSOLEBUFFER_LINE_MAXIMUM   1024

static uint8_t  console_buffer_backing_buffer[CONSOLEBUFFER_BUFFER_MAXIMUM] = {0};
static uint8_t* console_buffer_buffer                                       = NULL;
static size_t   console_buffer_maximum_usage                                = 0;
static size_t   console_buffer_current_usage                                = 0;

static void ConsoleBuffer_ExecuteBuffer();
static void ConsoleBuffer_ExecuteLine(const char* line);

void ConsoleBuffer_AddText(const char* command) {
    assert(command != NULL);

    size_t command_length = strlen(command);
    size_t final_length   = console_buffer_current_usage + command_length;

    if (final_length > console_buffer_maximum_usage) {
        Common_Log(LOG_LEVEL_WARNING, "Console buffer working_buffer overflowed.\n");

        return;
    }

    memcpy(&console_buffer_buffer[console_buffer_current_usage], command, command_length);
    console_buffer_current_usage += command_length;
}

void ConsoleBuffer_AddLine(const char* command) {
    char command_line[CONSOLEBUFFER_LINE_MAXIMUM] = {0};

    assert(command != NULL);

    snprintf(command_line, CONSOLEBUFFER_LINE_MAXIMUM, "%s\n", command);

    ConsoleBuffer_AddText(command_line);
}

void ConsoleBuffer_Start() {
    memset(console_buffer_backing_buffer, 0, CONSOLEBUFFER_BUFFER_MAXIMUM);

    console_buffer_buffer        = console_buffer_backing_buffer;
    console_buffer_maximum_usage = CONSOLEBUFFER_BUFFER_MAXIMUM;
    console_buffer_current_usage = 0;
}

void ConsoleBuffer_Stop() {
    console_buffer_current_usage = 0;
    console_buffer_maximum_usage = 0;
    console_buffer_buffer        = NULL;

    memset(console_buffer_backing_buffer, 0, CONSOLEBUFFER_BUFFER_MAXIMUM);
}

void ConsoleBuffer_Frame() {
    ConsoleBuffer_ExecuteBuffer();
}

static void ConsoleBuffer_ExecuteBuffer() {
    int64_t index                                    = 0;
    char*   working_buffer                           = NULL;
    char    working_line[CONSOLEBUFFER_LINE_MAXIMUM] = {0};
    int64_t quotes                                   = 0;

    while (console_buffer_current_usage > 0) {
        working_buffer = console_buffer_buffer;

        quotes = 0;
        for (index = 0; index < console_buffer_current_usage; index++) {
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

        if (index >= (CONSOLEBUFFER_LINE_MAXIMUM - 1)) {
            index = CONSOLEBUFFER_LINE_MAXIMUM - 1;
        }

        memcpy(working_line, working_buffer, index);
        working_line[index] = 0;

        if (index == console_buffer_current_usage) {
            console_buffer_current_usage = 0;
        } else {
            index++;
            console_buffer_current_usage -= index;
            memmove(working_buffer, working_buffer + index, console_buffer_current_usage);
        }

        ConsoleBuffer_ExecuteLine(working_line);
    }
}

static void ConsoleBuffer_ExecuteLine(const char* line) {
    assert(line != NULL);

    Command_Call(line);
}
