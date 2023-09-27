#include <drivers/tty.h>
#include <drivers/vga.h>
#include <lib/string.h>

void kernel_main(void)
{
    struct tty tty;
    char res[32] = {0};

    // vga_clear();
    itoa(vga_clear, res, 16);
    for (size_t x = 0; res[x]; x++) {
        vga_putc(x, 0, 0x0F, res[x]);
    }
    init_tty(&tty, (struct tty_print_interface) {
        .clear          = vga_clear,
        .display_char   = vga_putc,
        .display_int    = vga_printn,
        .display_string = vga_print,
    });
    // launch_tty(&tty);
    for (;;);
}
