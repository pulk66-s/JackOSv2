#include "Types/String/HeapString.hpp"
#include "kernel/Heap.hpp"

namespace JO::Libs::Types::String {
    HeapString::HeapString(const char *str)
    {
        this->init(str);
    }

    HeapString::HeapString(int value)
    {
        this->init(value);
    }

    void *HeapString::alloc(size_t size) const
    {
        return new char[size];
    }

    void HeapString::free(void *ptr) const
    {
        delete[] (char *)ptr;
    }
}