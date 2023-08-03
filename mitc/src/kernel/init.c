#include <include/memlayout.h>

void i386_init(void)
{
    unsigned char *vidmem = (unsigned char *)0xb8000 + KERNEL_BASE;

    vidmem[0] = 'H';
    vidmem[1] = 0x07;
    for (;;);
}