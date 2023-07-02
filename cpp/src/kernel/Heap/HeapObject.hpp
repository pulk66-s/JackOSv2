#ifndef __JACKOS_KERNEL_HEAP_HEAP_OBJECT_HPP__
    #define __JACKOS_KERNEL_HEAP_HEAP_OBJECT_HPP__

    #include <stddef.h>

class HeapObject
{
public:
    void *operator new(size_t size);
    void *operator new[](size_t size);
    void operator delete(void *ptr);
    void operator delete[](void *ptr);
};

#endif