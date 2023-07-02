#ifndef __CPPLIB_ARRAY_ARRAY_HPP__
    #define __CPPLIB_ARRAY_ARRAY_HPP__

    #include "Types/Array/AArray.hpp"
    #include <kernel/Heap.hpp>

template <typename T>
class Array : public AArray<T>, public HeapObject {
public:
    Array(size_t size) {
        this->init(size);
    }

    ~Array() {
        this->destroy();
    }

    void *alloc(size_t size) const {
        return new T[size];
    }

    void dealloc(void *p) const {
        delete[] (T*)p;
    }
};

#endif