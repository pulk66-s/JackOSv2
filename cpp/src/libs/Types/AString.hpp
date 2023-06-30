#ifndef __JACKOS_LIBS_TYPES_STRING_HPP__
    #define __JACKOS_LIBS_TYPES_STRING_HPP__

    #include <stddef.h>
    #include "kernel/Heap/HeapObject.hpp"

class AString
{
protected:
    char *str;
    size_t length;

    size_t strlen(const char *str) const;
    char *strdup(const char *str) const;
    virtual void *alloc(size_t size) const = 0;

public:
    AString(const char *str);

    char *c_str() const;

    // Size of the string
    size_t len() const;
};

#endif