#include <heaplib.h>

void *_globalHeap;
void malloc_init() {
    _globalHeap = CreateHeap(256 * 1024, 0);
}

void *malloc(size_t sz) {
    return AllocHeapMemory(_globalHeap, sz);
}

int free(void *ptr) {
    return FreeHeapMemory(_globalHeap, ptr);
}
