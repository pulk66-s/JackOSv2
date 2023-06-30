#include "Types/HeapString.hpp"
#include "kernel/Heap/Heap.hpp"

HeapString::HeapString(const char *str) : AString(str)
{
    this->str = this->strdup(str);
}

HeapString::~HeapString()
{
    delete[] this->str;
}

void *HeapString::alloc(size_t size) const
{
    return new char[size];
}