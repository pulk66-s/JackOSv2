#ifndef __JACKOS_LIBS_TYPES_STRING_HEAPSTRING_HPP__
    #define __JACKOS_LIBS_TYPES_STRING_HEAPSTRING_HPP__

    #include <stddef.h>
    #include <kernel/Heap.hpp>
    #include <Types/TypesNamespace.hpp>

    #include "Types/String/AString.hpp"

namespace JO::Libs::Types::String
{
    /**
     * @brief   This is a string class with all the functions you need.
     * This is an implementation of AString with the heap. Everything is stored in the
     * heap.
    */
    class HeapString : public AString, public HeapObject
    {
    protected:
        // Necessary to implement in the child class
        void *alloc(size_t size) const override;
        void free(void *ptr) const override;

    public:
        HeapString(const char *str);
        HeapString(int value);
    };
}

#endif