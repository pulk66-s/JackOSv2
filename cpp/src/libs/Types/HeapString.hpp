#ifndef __JACKOS_LIBS_TYPES_HEAPSTRING_HPP__
    #define __JACKOS_LIBS_TYPES_HEAPSTRING_HPP__

    #include <stddef.h>
    #include "kernel/Heap/HeapObject.hpp"
    #include "Types/AString.hpp"

class HeapString : public HeapObject, public AString
{
protected:
    void *alloc(size_t size) const override;

public:
    HeapString(const char *str);
    ~HeapString();
};

#endif