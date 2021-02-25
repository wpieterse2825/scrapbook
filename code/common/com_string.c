#include "common/com_public.h"
#include "common/com_local.h"

char* String_Allocate(size_t string_length) {
    assert(string_length > 0);

    return (char*)Memory_SystemAllocate(string_length, MEMORY_TAG_STRING);
}

void String_Free(char* input_string) {
    assert(input_string != NULL);

    Memory_SystemFree(input_string);
}

size_t String_Length(const char* input_string) {
    assert(input_string != NULL);

    return strlen(input_string);
}

bool String_Compare(const char* lhs, const char* rhs) {
    assert(lhs != NULL);
    assert(rhs != NULL);

    return strcmp(lhs, rhs) == 0;
}

bool String_CompareSize(const char* lhs, const char* rhs, size_t compare_size) {
    assert(lhs != NULL);
    assert(rhs != NULL);
    assert(compare_size > 0);

    return strncmp(lhs, rhs, compare_size) == 0;
}

void String_Copy(const char* source, char* destination) {
    assert(source != NULL);
    assert(destination != NULL);

    strcpy(destination, source);
}

void String_CopySize(const char* source, char* destination, size_t destination_length) {
    assert(source != NULL);
    assert(destination != NULL);
    assert(destination_length > 0);

    strncpy(destination, source, destination_length);
}

char* String_Clone(const char* input_string) {
    assert(input_string != NULL);

    size_t input_string_length = String_Length(input_string) + 1;
    char*  output_string       = String_Allocate(input_string_length);

    String_CopySize(input_string, output_string, input_string_length);

    return output_string;
}

void String_Print(char* buffer, size_t buffer_length, const char* format, ...) {
    va_list argument_list = {};

    va_start(argument_list, format);
    vsnprintf(buffer, buffer_length, format, argument_list);
    va_end(argument_list);
}

int64_t String_ToInteger(const char* source) {
    assert(source != NULL);

    return atol(source);
}

char* String_FromInteger(int64_t value) {
    char value_buffer[128] = {0};

    snprintf(value_buffer, 128, "%ld", value);

    return String_Clone(value_buffer);
}
