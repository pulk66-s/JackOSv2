#ifndef __JACKOS_LIBS_TYPES_STRING_HEAPSTRING_HPP__
    #define __JACKOS_LIBS_TYPES_STRING_HEAPSTRING_HPP__

    #include <stddef.h>
    #include <kernel/Heap.hpp>
    #include <Types/TypesNamespace.hpp>

    #include "Types/String/AString.hpp"

namespace JO::Libs::Types::String
{
    class HeapString : public AString, public HeapObject
    {
    protected:
        void *alloc(size_t size) const override;
        void dealloc(void *ptr) const override;

    public:
        HeapString(const char *str);
        HeapString(int value);
    };
}

#endif