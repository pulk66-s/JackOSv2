#ifndef __JACKOS_KERNEL_LIBS_TYPES_STRING_ASTRING_HPP__
    #define __JACKOS_KERNEL_LIBS_TYPES_STRING_ASTRING_HPP__

    #include <stddef.h>
    #include <stdint.h>
    #include <Types/TypesNamespace.hpp>

namespace JO::Libs::Types::String {
    class AString {
    private:
        char *str;
        size_t _len;

        size_t strlen(const char *str);
        char *strdup(const char *str);
        virtual void *alloc(size_t size) const = 0;
        virtual void dealloc(void *ptr) const = 0;
        char *itoa(int value);
        void revstr(char *str);

    public:
        void init(const char *str);
        void init(int value);

        char operator[](size_t index);
        size_t len();
        const char *c_str();
    };
}

#endif