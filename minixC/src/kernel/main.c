#include <drivers/tty.h>
#include <drivers/vga.h>
#include <lib/string.h>

void kernel_main(void)
{
    struct tty tty;
    char buff[16] = {0};

    itoa(123456789, buff, 10);
    vga_print(0, 1, 0x0F, buff);
    init_tty(&tty, (struct tty_print_interface) {
        .clear          = vga_clear,
        .display_char   = vga_putc,
        .display_int    = vga_printn,
        .display_string = vga_print,
    });
    launch_tty(&tty);
    for (;;);
}
