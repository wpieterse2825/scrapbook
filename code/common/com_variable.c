#include "common/com_shared.h"
#include "common/com_public.h"
#include "common/com_local.h"

#define VARIABLE_MAXIMUM 1024

typedef struct variable_s {
    bool     used;
    int64_t  handle;
    char*    key;
    char*    value;
    char*    default_value;
    uint64_t flags;
    bool     modified;
    int64_t  modification_count;
} variable_t;

static variable_t variables[VARIABLE_MAXIMUM] = {};
static int64_t    list_variables_command      = -1;

static variable_t* Variable_Find(const char* key);
static void        Variable_Command_List(command_arguments_t command_arguments);

int64_t Variable_Register(const char* key, const char* value, uint64_t flags) {
    int64_t     variable_index   = 0;
    variable_t* current_variable = NULL;

    assert(key != NULL);
    assert(value != NULL);

    current_variable = Variable_Find(key);

    if (current_variable != NULL) {
        Common_Error("Tried to register the variable '%s' with value '%s', but it already exists.", key, value);
    }

    for (variable_index = 0; variable_index < VARIABLE_MAXIMUM; variable_index++) {
        current_variable = &variables[variable_index];

        if (current_variable->used == false) {
            break;
        }
    }

    assert(variable_index < VARIABLE_MAXIMUM);

    current_variable->used               = true;
    current_variable->handle             = variable_index;
    current_variable->key                = String_Clone(key);
    current_variable->value              = String_Clone(value);
    current_variable->default_value      = String_Clone(value);
    current_variable->flags              = flags;
    current_variable->modified           = true;
    current_variable->modification_count = 1;

    return variable_index;
}

void Variable_Unregister(int64_t variable_handle) {
    if (variable_handle < 0) {
        return;
    }

    if (variable_handle >= VARIABLE_MAXIMUM) {
        return;
    }

    variable_t* current_variable = &variables[variable_handle];

    if (current_variable->used == false) {
        return;
    }

    current_variable->used   = false;
    current_variable->handle = -1;

    String_Free(current_variable->key);
    current_variable->key = NULL;

    String_Free(current_variable->value);
    current_variable->value = NULL;

    String_Free(current_variable->default_value);
    current_variable->default_value = NULL;

    current_variable->flags              = 0;
    current_variable->modified           = false;
    current_variable->modification_count = 0;
}

void Variable_Reset(int64_t variable_handle) {
    if (variable_handle < 0) {
        return;
    }

    if (variable_handle >= VARIABLE_MAXIMUM) {
        return;
    }

    variable_t* current_variable = &variables[variable_handle];

    if (current_variable->used == false) {
        return;
    }

    if (current_variable->flags & VARIABLE_FLAG_STATIC) {
        Common_Print(PRINT_LEVEL_WARNING, "Tried to reset the static variable '%s'!\n", current_variable->key);

        return;
    }

    String_Free(current_variable->value);

    current_variable->value    = String_Clone(current_variable->default_value);
    current_variable->modified = true;
    current_variable->modification_count++;
}

const char* Variable_GetString(int64_t variable_handle) {
    if (variable_handle < 0) {
        return "";
    }

    if (variable_handle >= VARIABLE_MAXIMUM) {
        return "";
    }

    variable_t* current_variable = &variables[variable_handle];

    if (current_variable->used == false) {
        return "";
    }

    return current_variable->value;
}

void Variable_SetString(int64_t variable_handle, const char* value) {
    if (variable_handle < 0) {
        return;
    }

    if (variable_handle >= VARIABLE_MAXIMUM) {
        return;
    }

    variable_t* current_variable = &variables[variable_handle];

    if (current_variable->used == false) {
        return;
    }

    if (current_variable->flags & VARIABLE_FLAG_STATIC) {
        Common_Print(PRINT_LEVEL_WARNING, "Tried to set the static variable '%s'!\n", current_variable->key);

        return;
    }

    String_Free(current_variable->value);

    current_variable->value    = String_Clone(value);
    current_variable->modified = true;
    current_variable->modification_count++;
}

int64_t Variable_GetInteger(int64_t variable_handle) {
    if (variable_handle < 0) {
        return 0;
    }

    if (variable_handle >= VARIABLE_MAXIMUM) {
        return 0;
    }

    variable_t* current_variable = &variables[variable_handle];

    if (current_variable->used == false) {
        return 0;
    }

    return String_ToInteger(current_variable->value);
}

void Variable_SetInteger(int64_t variable_handle, int64_t value) {
    char value_buffer[1024] = {0};

    if (variable_handle < 0) {
        return;
    }

    if (variable_handle >= VARIABLE_MAXIMUM) {
        return;
    }

    variable_t* current_variable = &variables[variable_handle];

    if (current_variable->used == false) {
        return;
    }

    if (current_variable->flags & VARIABLE_FLAG_STATIC) {
        Common_Print(PRINT_LEVEL_WARNING, "Tried to set the static variable '%s'!\n", current_variable->key);

        return;
    }

    String_Free(current_variable->value);

    current_variable->value    = String_FromInteger(value);
    current_variable->modified = true;
    current_variable->modification_count++;
}

bool Variable_IsModified(int64_t variable_handle) {
    if (variable_handle < 0) {
        return false;
    }

    if (variable_handle >= VARIABLE_MAXIMUM) {
        return false;
    }

    variable_t* current_variable = &variables[variable_handle];

    if (current_variable->used == false) {
        return false;
    }

    return current_variable->modified;
}

int64_t Variable_ModificationCount(int64_t variable_handle) {
    if (variable_handle < 0) {
        return 0;
    }

    if (variable_handle >= VARIABLE_MAXIMUM) {
        return 0;
    }

    variable_t* current_variable = &variables[variable_handle];

    if (current_variable->used == false) {
        return 0;
    }

    return current_variable->modification_count;
}

void Variable_ClearModified(int64_t variable_handle) {
    if (variable_handle < 0) {
        return;
    }

    if (variable_handle >= VARIABLE_MAXIMUM) {
        return;
    }

    variable_t* current_variable = &variables[variable_handle];

    if (current_variable->used == false) {
        return;
    }

    current_variable->modified = false;
}

void Variable_Start() {
    list_variables_command = Command_Register("list_variables", Variable_Command_List, COMMAND_FLAG_PRODUCTION | COMMAND_FLAG_SYSTEM);
}

void Variable_Stop() {
    Command_Unregister(list_variables_command);

    list_variables_command = -1;
}

void Variable_Frame() {
}

static variable_t* Variable_Find(const char* key) {
    variable_t* current_variable = NULL;

    for (size_t variable_index = 0; variable_index < VARIABLE_MAXIMUM; variable_index++) {
        current_variable = &variables[variable_index];

        if (current_variable->used == false) {
            continue;
        }

        if (String_Compare(current_variable->key, key)) {
            return current_variable;
        }
    }

    return NULL;
}

static void Variable_Command_List(command_arguments_t command_arguments) {
    bool variable_found = false;
    bool print_system   = false;
    bool print_renderer = false;
    bool print_sound    = false;
    bool print_input    = false;
    bool print_network  = false;
    bool print_tool     = false;
    bool print_game     = false;

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

            if (String_Compare(current_argument, "system")) {
                print_system = true;
            } else if (String_Compare(current_argument, "renderer")) {
                print_renderer = true;
            } else if (String_Compare(current_argument, "sound")) {
                print_sound = true;
            } else if (String_Compare(current_argument, "input")) {
                print_input = true;
            } else if (String_Compare(current_argument, "network")) {
                print_network = true;
            } else if (String_Compare(current_argument, "tool")) {
                print_tool = true;
            } else if (String_Compare(current_argument, "game")) {
                print_game = true;
            } else {
                Common_Print(PRINT_LEVEL_WARNING, "Unknown variable type '%s'!\n", current_argument);
                return;
            }
        }
    }

    for (size_t variable_index = 0; variable_index < VARIABLE_MAXIMUM; variable_index++) {
        variable_t* current_variable = &variables[variable_index];

        if (current_variable->used == true) {
            variable_found = true;

            if (current_variable->flags & VARIABLE_FLAG_PRODUCTION) {
                Common_Print(PRINT_LEVEL_INFORMATION, "P");
            } else {
                Common_Print(PRINT_LEVEL_INFORMATION, "D");
            }

            if (current_variable->flags & VARIABLE_FLAG_STATIC) {
                Common_Print(PRINT_LEVEL_INFORMATION, "S");
            } else {
                Common_Print(PRINT_LEVEL_INFORMATION, "D");
            }

            if (current_variable->flags & VARIABLE_FLAG_READ_ONLY) {
                Common_Print(PRINT_LEVEL_INFORMATION, "R");
            } else {
                Common_Print(PRINT_LEVEL_INFORMATION, "W");
            }

            if (current_variable->flags & VARIABLE_FLAG_ARCHIVE) {
                Common_Print(PRINT_LEVEL_INFORMATION, "A");
            } else {
                Common_Print(PRINT_LEVEL_INFORMATION, "T");
            }

            if (current_variable->flags & VARIABLE_FLAG_CHEAT) {
                Common_Print(PRINT_LEVEL_INFORMATION, "C");
            } else {
                Common_Print(PRINT_LEVEL_INFORMATION, "N");
            }

            if (current_variable->flags & VARIABLE_FLAG_SYSTEM) {
                if (print_system == false) {
                    continue;
                } else {
                    Common_Print(PRINT_LEVEL_INFORMATION, "X");
                }
            } else if (current_variable->flags & VARIABLE_FLAG_RENDERER) {
                if (print_system == false) {
                    continue;
                } else {
                    Common_Print(PRINT_LEVEL_INFORMATION, "R");
                }
            } else if (current_variable->flags & VARIABLE_FLAG_SOUND) {
                if (print_system == false) {
                    continue;
                } else {
                    Common_Print(PRINT_LEVEL_INFORMATION, "S");
                }
            } else if (current_variable->flags & VARIABLE_FLAG_INPUT) {
                if (print_system == false) {
                    continue;
                } else {
                    Common_Print(PRINT_LEVEL_INFORMATION, "I");
                }
            } else if (current_variable->flags & VARIABLE_FLAG_NETWORK) {
                if (print_system == false) {
                    continue;
                } else {
                    Common_Print(PRINT_LEVEL_INFORMATION, "N");
                }
            } else if (current_variable->flags & VARIABLE_FLAG_TOOL) {
                if (print_system == false) {
                    continue;
                } else {
                    Common_Print(PRINT_LEVEL_INFORMATION, "T");
                }
            } else if (current_variable->flags & VARIABLE_FLAG_GAME) {
                if (print_system == false) {
                    continue;
                } else {
                    Common_Print(PRINT_LEVEL_INFORMATION, "G");
                }
            }

            Common_Print(PRINT_LEVEL_INFORMATION,
                         " - %-32s - %-16s - %s\n",
                         current_variable->key,
                         current_variable->value,
                         current_variable->default_value);
        }
    }

    if (variable_found == false) {
        Common_Print(PRINT_LEVEL_INFORMATION, "No variables registered.\n");
    }
}
