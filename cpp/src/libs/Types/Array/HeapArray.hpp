#ifndef __JACKOS_LIBS_TYPES_ARRAY_HEAPARRAY_HPP__
    #define __JACKOS_LIBS_TYPES_ARRAY_HEAPARRAY_HPP__

    #include "Types/Array/AArray.hpp"
    #include <kernel/Heap.hpp>
    #include <Types/TypesNamespace.hpp>

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

        void *alloc(size_t size) const
        {
            return new T[size];
        }

        void dealloc(void *p) const
        {
            delete[] (T *)p;
        }
    };
}

#endif