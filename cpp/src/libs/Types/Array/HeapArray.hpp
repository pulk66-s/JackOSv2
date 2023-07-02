#ifndef __JACKOS_LIBS_TYPES_ARRAY_HEAPARRAY_HPP__
    #define __JACKOS_LIBS_TYPES_ARRAY_HEAPARRAY_HPP__

    #include <kernel/Heap.hpp>
    #include <Types/TypesNamespace.hpp>

    #include "Types/Array/AArray.hpp"

/**
 * @brief   This is an array class with all the functions you need.
 * This is an implementation of AArray with the heap. Everything is stored in the
 * heap.
*/
namespace JO::Libs::Types::Array
{

    template <typename T>
    class HeapArray : public AArray<T>, public HeapObject {
    public:
        HeapArray(size_t size)
        {
            this->init(size);
        }

        ~HeapArray()
        {
            this->destroy();
        }

        // function to alloc necessary memory, It's defined in HeapObject
        void *alloc(size_t size) const
        {
            return new T[size];
        }

        // function to free necessary memory, It's defined in HeapObject
        void free(void *p) const
        {
            delete[] (T *)p;
        }
    };
}

#endif