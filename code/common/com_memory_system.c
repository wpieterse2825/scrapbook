#include "common/com_shared.h"
#include "common/com_public.h"
#include "common/com_local.h"

void* Memory_SystemAllocate(size_t length, memory_tag_e tag) {
    assert(length > 0);

    return malloc(length);
}

void Memory_SystemFree(void* buffer) {
    assert(buffer != NULL);

    free(buffer);
}
