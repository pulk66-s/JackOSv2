#ifndef __CPPLIB_ARRAY_AARRAY_HPP__
    #define __CPPLIB_ARRAY_AARRAY_HPP__

#include <stddef.h>

template <typename T>
class AArray {
private:
    T* _data;
    size_t _size;

public:
    virtual void *alloc(size_t size) const = 0;
    virtual void dealloc(void *p) const = 0;

    void init(size_t size) {
        this->_size = size;
        this->_data = (T*)this->alloc(size);
    }

    void destroy() {
        this->dealloc(this->_data);
    }

    size_t len() const {
        return this->_size;
    }

    T& operator[](size_t index) {
        return this->_data[index];
    }

    void fill(T value) {
        for (size_t i = 0; i < this->_size; i++) {
            this->_data[i] = value;
        }
    }
};

#endif