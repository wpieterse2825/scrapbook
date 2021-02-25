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

variable_t variables[VARIABLE_MAXIMUM] = {};
int64_t    variable_command_list       = -1;

static variable_t* Variable_Find(const char* key);
static void        Variable_Command_List(command_arguments_t command_arguments);

void Variable_Start() {
    variable_command_list = Command_Register("list_variables", Variable_Command_List);
}

void Variable_Stop() {
    Command_Unregister(variable_command_list);
    variable_command_list = -1;
}

void Variable_Frame() {
}

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
    current_variable->key                = String_Copy(key);
    current_variable->value              = String_Copy(value);
    current_variable->default_value      = String_Copy(value);
    current_variable->flags              = flags;
    current_variable->modified           = true;
    current_variable->modification_count = 1;

    return variable_index;
}

void Variable_Unregister(int64_t variable_handle) {
    assert(variable_handle >= 0);
    assert(variable_handle < VARIABLE_MAXIMUM);

    variable_t* current_variable = &variables[variable_handle];

    assert(current_variable->used == true);

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
    assert(variable_handle >= 0);
    assert(variable_handle < VARIABLE_MAXIMUM);

    variable_t* current_variable = &variables[variable_handle];

    assert(current_variable->used == true);

    String_Free(current_variable->value);

    current_variable->value    = String_Copy(current_variable->default_value);
    current_variable->modified = true;
    current_variable->modification_count++;
}

const char* Variable_GetString(int64_t variable_handle) {
    assert(variable_handle >= 0);
    assert(variable_handle < VARIABLE_MAXIMUM);

    variable_t* current_variable = &variables[variable_handle];

    assert(current_variable->used == true);

    return current_variable->value;
}

void Variable_SetString(int64_t variable_handle, const char* value) {
    assert(variable_handle >= 0);
    assert(variable_handle < VARIABLE_MAXIMUM);

    variable_t* current_variable = &variables[variable_handle];

    assert(current_variable->used == true);

    String_Free(current_variable->value);

    current_variable->value    = String_Copy(value);
    current_variable->modified = true;
    current_variable->modification_count++;
}

int64_t Variable_GetInteger(int64_t variable_handle) {
    assert(variable_handle >= 0);
    assert(variable_handle < VARIABLE_MAXIMUM);

    variable_t* current_variable = &variables[variable_handle];

    assert(current_variable->used == true);

    return atol(current_variable->value);
}

void Variable_SetInteger(int64_t variable_handle, int64_t value) {
    char value_buffer[1024] = {0};

    assert(variable_handle >= 0);
    assert(variable_handle < VARIABLE_MAXIMUM);

    variable_t* current_variable = &variables[variable_handle];

    assert(current_variable->used == true);

    String_Free(current_variable->value);

    snprintf(value_buffer, 1024, "%ld", value);

    current_variable->value    = String_Copy(value_buffer);

    current_variable->modified = true;
    current_variable->modification_count++;
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

    for (size_t variable_index = 0; variable_index < VARIABLE_MAXIMUM; variable_index++) {
        variable_t* current_variable = &variables[variable_index];

        if (current_variable->used == true) {
            variable_found = true;

            Common_Log(
              LOG_LEVEL_INFORMATION, "%s - %s - %s\n", current_variable->key, current_variable->value, current_variable->default_value);
        }
    }

    if (variable_found == false) {
        Common_Log(LOG_LEVEL_INFORMATION, "No variables registered.\n");
    }
}
