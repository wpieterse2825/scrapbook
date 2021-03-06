#include "common/com_shared.h"
#include "common/com_public.h"
#include "common/com_local.h"

#define COMMAND_MAXIMUM      1024
#define COMMAND_MAXIMUM_NAME 64

typedef struct command_s {
    bool             used;
    int64_t          handle;
    char*            name;
    command_callback callback;
    uint64_t         flags;
} command_t;

static command_t commands[COMMAND_MAXIMUM] = {};
static int64_t   list_commands_command     = -1;

static command_arguments_t Command_TokenizeLine(const char* line);
static command_t*          Command_Find(const char* name);
static void                Command_Command_List(command_arguments_t command_arguments);

int64_t Command_Register(const char* name, command_callback callback, uint64_t flags) {
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
    current_command->flags    = flags;

    return command_index;
}

void Command_Unregister(int64_t command_handle) {
    if (command_handle < 0) {
        return;
    }

    if (command_handle >= COMMAND_MAXIMUM) {
        return;
    }

    command_t* current_command = &commands[command_handle];
    if (current_command->used == false) {
        return;
    }

    current_command->used   = false;
    current_command->handle = -1;

    String_Free(current_command->name);
    current_command->name = NULL;

    current_command->callback = NULL;
    current_command->flags    = 0;
}

void Command_Start() {
    list_commands_command = Command_Register("list_commands", Command_Command_List, COMMAND_FLAG_PRODUCTION | COMMAND_FLAG_SYSTEM);
}

void Command_Stop() {
    Command_Unregister(list_commands_command);

    list_commands_command = -1;
}

void Command_Frame() {
}

bool Command_CallConsole(const char* line) {
    assert(line != NULL);

    command_arguments_t command_arguments = Command_TokenizeLine(line);
    if (command_arguments.argument_count == 0) {
        Common_Print(PRINT_LEVEL_WARNING, "Invalid command passed to command system.\n");

        return false;
    }

    const char* command_name    = command_arguments.arguments[0];
    command_t*  current_command = Command_Find(command_name);
    if (current_command == NULL) {
        Common_Print(PRINT_LEVEL_DEVELOPER, "Unknown command : %s.\n", command_name);

        return false;
    }

    current_command->callback(command_arguments);

    return true;
}

// TODO(wpieterse): Improve this.
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

        if (String_Compare(current_command->name, name, COMMAND_MAXIMUM_NAME)) {
            return current_command;
        }
    }

    return NULL;
}

void Command_Command_List(command_arguments_t command_arguments) {
    bool any_commands_found = false;
    bool print_system       = false;
    bool print_renderer     = false;
    bool print_sound        = false;
    bool print_input        = false;
    bool print_network      = false;
    bool print_tool         = false;
    bool print_game         = false;

    if (command_arguments.argument_count == 1) {
        print_system   = true;
        print_renderer = true;
        print_sound    = true;
        print_input    = true;
        print_network  = true;
        print_tool     = true;
        print_game     = true;
    } else {
        for (size_t argument_index = 1; argument_index < command_arguments.argument_count; argument_index++) {
            const char* current_argument = command_arguments.arguments[argument_index];

            if (String_Compare(current_argument, "system", COMMAND_LINE_MAXIMUM)) {
                print_system = true;
            } else if (String_Compare(current_argument, "renderer", COMMAND_LINE_MAXIMUM)) {
                print_renderer = true;
            } else if (String_Compare(current_argument, "sound", COMMAND_LINE_MAXIMUM)) {
                print_sound = true;
            } else if (String_Compare(current_argument, "input", COMMAND_LINE_MAXIMUM)) {
                print_input = true;
            } else if (String_Compare(current_argument, "network", COMMAND_LINE_MAXIMUM)) {
                print_network = true;
            } else if (String_Compare(current_argument, "tool", COMMAND_LINE_MAXIMUM)) {
                print_tool = true;
            } else if (String_Compare(current_argument, "game", COMMAND_LINE_MAXIMUM)) {
                print_game = true;
            } else {
                Common_Print(PRINT_LEVEL_WARNING, "Unknown command type '%s'!\n", current_argument);
                return;
            }
        }
    }

    for (size_t command_index = 0; command_index < COMMAND_MAXIMUM; command_index++) {
        command_t* current_command = &commands[command_index];

        if (current_command->used == true) {
            any_commands_found = true;

            if (current_command->flags & COMMAND_FLAG_PRODUCTION) {
                Common_Print(PRINT_LEVEL_INFORMATION, "P");
            } else {
                Common_Print(PRINT_LEVEL_INFORMATION, "D");
            }

            if (current_command->flags & COMMAND_FLAG_CHEAT) {
                Common_Print(PRINT_LEVEL_INFORMATION, "C");
            } else {
                Common_Print(PRINT_LEVEL_INFORMATION, "N");
            }

            if (current_command->flags & COMMAND_FLAG_SYSTEM) {
                if (print_system == false) {
                    continue;
                } else {
                    Common_Print(PRINT_LEVEL_INFORMATION, "X");
                }
            } else if (current_command->flags & COMMAND_FLAG_RENDERER) {
                if (print_renderer == false) {
                    continue;
                } else {
                    Common_Print(PRINT_LEVEL_INFORMATION, "R");
                }
            } else if (current_command->flags & COMMAND_FLAG_SOUND) {
                if (print_sound == false) {
                    continue;
                } else {
                    Common_Print(PRINT_LEVEL_INFORMATION, "S");
                }
            } else if (current_command->flags & COMMAND_FLAG_INPUT) {
                if (print_input == false) {
                    continue;
                } else {
                    Common_Print(PRINT_LEVEL_INFORMATION, "I");
                }
            } else if (current_command->flags & COMMAND_FLAG_NETWORK) {
                if (print_network == false) {
                    continue;
                } else {
                    Common_Print(PRINT_LEVEL_INFORMATION, "N");
                }
            } else if (current_command->flags & COMMAND_FLAG_TOOL) {
                if (print_tool == false) {
                    continue;
                } else {
                    Common_Print(PRINT_LEVEL_INFORMATION, "T");
                }
            } else if (current_command->flags & COMMAND_FLAG_GAME) {
                if (print_game == false) {
                    continue;
                } else {
                    Common_Print(PRINT_LEVEL_INFORMATION, "G");
                }
            }

            Common_Print(PRINT_LEVEL_INFORMATION, " - %-32s\n", current_command->name);
        }
    }

    if (any_commands_found == false) {
        Common_Print(PRINT_LEVEL_INFORMATION, "No commands registered.\n");
    }
}
