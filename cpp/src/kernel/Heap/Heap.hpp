#ifndef __JACKOS_KERNEL_HEAP_HEAP_HPP__
    #define __JACKOS_KERNEL_HEAP_HEAP_HPP__

    #include <stddef.h>
    #include <stdint.h>

    #define HEAP_START 0x1000
    #define HEAP_SIZE  0x1000

void *kHeapAlloc(size_t size);
void *operator new(size_t size);
void *operator new[](size_t size);
void operator delete(void *ptr);
void operator delete[](void *ptr);

#endif