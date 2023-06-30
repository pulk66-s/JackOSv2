#include "kernel/Heap/Heap.hpp"
#include "kernel/VGA/VGA.hpp"

static uint8_t *heap_start = (uint8_t *)HEAP_START;
static uint8_t *heap_current = (uint8_t *)HEAP_START;
static uint8_t *heap_end = (uint8_t *)(HEAP_START + HEAP_SIZE);

void *kHeapAlloc(size_t size)
{
    if (heap_current + size > heap_end) {
        return nullptr;
    }

    void *ptr = heap_current;

    heap_current += size;
    return ptr;
}

void *operator new(size_t size)
{
    return kHeapAlloc(size);
}

void *operator new[](size_t size)
{
    return kHeapAlloc(size);
}

void operator delete(void *ptr)
{
    // Do nothing.
}

void operator delete[](void *ptr)
{
    // Do nothing.
}