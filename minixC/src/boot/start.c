#include "boot.h"

/**
 * @brief   Main entry point at boot, called from boot.asm
 * It enables the A20 line, switches to 32-bit mode
*/
void start_boot(void)
{
    for (;;);
    print_char_16('S');
    print_char_16('E');
    print_char_16('X');
}
