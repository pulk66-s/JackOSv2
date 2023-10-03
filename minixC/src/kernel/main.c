#include <drivers/tty.h>
#include <drivers/vga.h>
#include <drivers/pic.h>
#include <drivers/ps2/keyboard.h>
#include <lib/string.h>
#include <interrupts.h>

void kernel_main(void)
{
    struct tty tty;
    char buff[16] = {0};

    vga_clear();
    vga_print(0, 0, 0x0F, "Starting kernel...\n");
    init_tty(&tty, (struct tty_print_interface) {
        .clear          = vga_clear,
        .display_char   = vga_putc,
        .display_int    = vga_printn,
        .display_string = vga_print,
    });
    idt_setup();
    init_ps2_keyboard();
    launch_tty(&tty);
    for (;;);
}
