#include <include/clib/string.h>
#include <include/console.h>
#include <include/graphics/CGA.h>

int i386_init(void)
{
    // unsigned char *cga_buffer = (unsigned char *)CGA_BASE;

    // cga_buffer[0] = '!';
    // cga_buffer[1] = 0x0f;
    // cga_init();
    // cga_putc('!', 0, 0, CGA_COLOR(CGA_COLOR_WHITE, CGA_COLOR_BLACK));
    console_init(NULL);
    kcons_printc('!');
    kcons_prints("Hello, world!");
    kcons_printn(42);
    kcons_printc('!');
    for (;;);
}