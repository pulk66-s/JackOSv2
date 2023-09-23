#include "include/boot.h"

void print_char(char c)
{
    char *video = (char *)0xb8000;
    *video = c;
    *(video + 1) = 0x0F;
}

void start_boot(void)
{
    print_char('A');
    for (;;);
}
