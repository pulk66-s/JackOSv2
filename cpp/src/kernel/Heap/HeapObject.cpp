#include "kernel/Heap/HeapObject.hpp"
#include "kernel/Heap/Heap.hpp"

void *HeapObject::operator new(size_t size)
{
    return kHeapAlloc(size);
}

void *HeapObject::operator new[](size_t size)
{
    return kHeapAlloc(size);
}

void HeapObject::operator delete(void *ptr)
{
    // Do nothing.
}

void HeapObject::operator delete[](void *ptr)
{
    // Do nothing.
}