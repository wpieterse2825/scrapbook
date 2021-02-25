#include "common/com_public.h"
#include "common/com_local.h"

char* String_Allocate(size_t string_length) {
    assert(string_length > 0);

    return (char*)malloc(string_length);
}

void String_Free(char* input_string) {
    assert(input_string != NULL);

    free(input_string);
}

char* String_Copy(const char* input_string) {
    assert(input_string != NULL);

    size_t input_string_length = strlen(input_string) + 1;
    char*  output_string       = String_Allocate(input_string_length);

    strncpy(output_string, input_string, input_string_length);

    return output_string;
}

bool String_Compare(const char* lhs, const char* rhs) {
    assert(lhs != NULL);
    assert(rhs != NULL);

    return strcmp(lhs, rhs) == 0;
}
