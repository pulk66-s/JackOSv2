#ifndef __JACKOS_KERNEL_LIBS_TYPES_STRING_ASTRING_HPP__
    #define __JACKOS_KERNEL_LIBS_TYPES_STRING_ASTRING_HPP__

    #include <stddef.h>
    #include <stdint.h>
    #include <Types/TypesNamespace.hpp>

namespace JO::Libs::Types::String {
    /**
     * @brief       This is an abstract of a string class with all the functions you need.
     * To manage a string.
     * @attention   You need to implement the alloc and free methods.
    */
    class AString {
    private:
        char *str;
        size_t _len;

        // CFunctions implementation
        size_t strlen(const char *str);
        char *strdup(const char *str);
        char *itoa(int value);
        void revstr(char *str);

        // Necessary to implement in the child class
        virtual void *alloc(size_t size) const = 0;
        virtual void free(void *ptr) const = 0;

    public:
        void init(const char *str);
        void init(int value);
        void destroy();

        // Access to the data at index i
        char operator[](size_t index);
        size_t len();

        // give the string as a const char *
        const char *c_str();
    };
}

#endif