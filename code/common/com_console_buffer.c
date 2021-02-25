#include "common/com_public.h"
#include "common/com_local.h"

static uint8_t  buffer_storage[PARSE_BUFFER_MAXIMUM] = {0};
static uint8_t* buffer_pointer                       = NULL;
static size_t   maximum_size                         = 0;
static size_t   current_size                         = 0;

static void ConsoleBuffer_ExecuteBuffer();
static void ConsoleBuffer_ExecuteLine(const char* line);

void ConsoleBuffer_AddText(const char* command) {
    assert(command != NULL);

    size_t command_length = strlen(command);
    size_t final_length   = current_size + command_length;

    if (final_length > maximum_size) {
        Common_Log(LOG_LEVEL_WARNING, "Console buffer overflowed.\n");

        return;
    }

    memcpy(&buffer_pointer[current_size], command, command_length);
    current_size += command_length;
}

void ConsoleBuffer_AddLine(const char* command) {
    char command_line[COMMAND_LINE_MAXIMUM] = {0};

    assert(command != NULL);

    String_Print(command_line, COMMAND_LINE_MAXIMUM, "%s\n", command);

    ConsoleBuffer_AddText(command_line);
}

void ConsoleBuffer_Start() {
    memset(buffer_storage, 0, PARSE_BUFFER_MAXIMUM);

    buffer_pointer = buffer_storage;
    maximum_size   = PARSE_BUFFER_MAXIMUM;
    current_size   = 0;
}

void ConsoleBuffer_Stop() {
    current_size   = 0;
    maximum_size   = 0;
    buffer_pointer = NULL;

    memset(buffer_storage, 0, PARSE_BUFFER_MAXIMUM);
}

void ConsoleBuffer_Frame() {
    ConsoleBuffer_ExecuteBuffer();
}

static void ConsoleBuffer_ExecuteBuffer() {
    int64_t index                              = 0;
    char*   working_buffer                     = NULL;
    char    working_line[COMMAND_LINE_MAXIMUM] = {0};
    int64_t quotes                             = 0;

    while (current_size > 0) {
        working_buffer = buffer_pointer;

        quotes = 0;
        for (index = 0; index < current_size; index++) {
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

        if (index >= (COMMAND_LINE_MAXIMUM - 1)) {
            index = COMMAND_LINE_MAXIMUM - 1;
        }

        memcpy(working_line, working_buffer, index);
        working_line[index] = 0;

        if (index == current_size) {
            current_size = 0;
        } else {
            index++;
            current_size -= index;
            memmove(working_buffer, working_buffer + index, current_size);
        }

        ConsoleBuffer_ExecuteLine(working_line);
    }
}

static void ConsoleBuffer_ExecuteLine(const char* line) {
    assert(line != NULL);

    Command_Call(line);
}
