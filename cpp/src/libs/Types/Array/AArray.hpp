#ifndef __JACKOS_LIBS_TYPES_ARRAY_AARRAY_HPP__
    #define __JACKOS_LIBS_TYPES_ARRAY_AARRAY_HPP__

    #include <stddef.h>
    #include <Types/TypesNamespace.hpp>

namespace JO::Libs::Types::Array
{
    /**
     * @brief       This is an abstract of an array class with all the functions you need.
     * To manage an array with a defined size.
     * @attention   You need to implement the alloc and free methods.
     * @tparam  T   The type of the array.
    */
    template <typename T>
    class AArray {
    private:
        T* _data;
        size_t _size;

    public:
        virtual void *alloc(size_t size) const = 0;
        virtual void free(void *p) const = 0;

        // function to call in constructor
        void init(size_t size) {
            this->_size = size;
            this->_data = (T*)this->alloc(size);
        }

        // function to call in destructor
        void destroy() {
            this->free(this->_data);
        }

        size_t len() const {
            return this->_size;
        }

        // Access to the data at index i
        T& operator[](size_t index) {
            return this->_data[index];
        }

        // Fill all the array with the value
        void fill(T value) {
            for (size_t i = 0; i < this->_size; i++) {
                this->_data[i] = value;
            }
        }
    };
}
#endif