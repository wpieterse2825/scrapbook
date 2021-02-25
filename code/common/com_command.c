#include "common/com_shared.h"
#include "common/com_public.h"
#include "common/com_local.h"

#define COMMAND_MAXIMUM 1024

typedef struct command_s {
    bool             used;
    int64_t          handle;
    char*            name;
    command_callback callback;
} command_t;

static command_t commands[COMMAND_MAXIMUM] = {};
static int64_t   list_commands_command      = -1;

static command_arguments_t Command_TokenizeLine(const char* line);
static command_t*          Command_Find(const char* name);
static void                Command_Command_List(command_arguments_t command_arguments);

void Command_Start() {
    list_commands_command = Command_Register("list_commands", Command_Command_List);
}

void Command_Stop() {
    Command_Unregister(list_commands_command);

    list_commands_command = -1;
}

void Command_Frame() {
}

int64_t Command_Register(const char* name, command_callback callback) {
    int64_t    command_index   = 0;
    command_t* current_command = NULL;

    assert(name != NULL);
    assert(callback != NULL);

    current_command = Command_Find(name);

    if (current_command != NULL) {
        if (current_command->callback != NULL) {
            Common_Print(PRINT_LEVEL_WARNING, "Tried to register the command '%s', but it already exists.", name);
        }

        return -1;
    }

    for (command_index = 0; command_index < COMMAND_MAXIMUM; command_index++) {
        current_command = &commands[command_index];

        if (current_command->used == false) {
            break;
        }
    }

    assert(command_index < COMMAND_MAXIMUM);

    current_command->used     = true;
    current_command->handle   = command_index;
    current_command->name     = String_Clone(name);
    current_command->callback = callback;

    return command_index;
}

void Command_Unregister(int64_t command_handle) {
    if(command_handle < 0) {
        return;
    }

    if(command_handle >= COMMAND_MAXIMUM) {
        return;
    }

    command_t* current_command = &commands[command_handle];

    if(current_command->used == false) {
        return;
    }

    current_command->used   = false;
    current_command->handle = -1;

    String_Free(current_command->name);
    current_command->name = NULL;

    current_command->callback = NULL;
}

void Command_Call(const char* line) {
    assert(line != NULL);

    command_arguments_t command_arguments = Command_TokenizeLine(line);
    const char*         command_name      = command_arguments.arguments[0];

    command_t* current_command = Command_Find(command_name);
    if (current_command == NULL) {
        Common_Error("Tried to call the command '%s', but it is not registered.", command_name);
    }

    current_command->callback(command_arguments);
}

command_arguments_t Command_TokenizeLine(const char* line) {
    command_arguments_t result           = {};
    bool                still_processing = true;
    size_t              input_line_index = 0;
    size_t              argument_index   = 0;

    assert(line != NULL);

    while (still_processing == true) {
        char current_character = line[input_line_index];
        if (current_character == '\0') {
            result.arguments[result.argument_count][argument_index] = '\0';
            result.argument_count++;

            still_processing = false;
        } else if (current_character == ' ') {
            result.arguments[result.argument_count][argument_index] = '\0';

            result.argument_count++;
            if (result.argument_count == COMMAND_ARGUMENT_MAXIMUM) {
                Common_Error("Tokenization of arguments exceeded maximum argument count.");
            }

            argument_index = 0;
        } else {
            result.arguments[result.argument_count][argument_index] = current_character;
            argument_index++;

            if (argument_index == COMMAND_LINE_MAXIMUM) {
                Common_Error("Tokenization of argument string exceeded maximum limit.");
            }
        }

        input_line_index++;
    }

    return result;
}

command_t* Command_Find(const char* name) {
    for (size_t command_index = 0; command_index < COMMAND_MAXIMUM; command_index++) {
        command_t* current_command = &commands[command_index];

        if (current_command->used == false) {
            continue;
        }

        if (String_Compare(current_command->name, name)) {
            return current_command;
        }
    }

    return NULL;
}

void Command_Command_List(command_arguments_t command_arguments) {
    bool command_found = false;

    for (size_t command_index = 0; command_index < COMMAND_MAXIMUM; command_index++) {
        command_t* current_command = &commands[command_index];

        if (current_command->used == true) {
            command_found = true;

            Common_Print(PRINT_LEVEL_INFORMATION, " * %s\n", current_command->name);
        }
    }

    if (command_found == false) {
        Common_Print(PRINT_LEVEL_INFORMATION, "No commands registered.\n");
    }
}
