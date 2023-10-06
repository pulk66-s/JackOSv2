#include <drivers/tty.h>
#include <drivers/vga.h>
#include <drivers/pic.h>
#include <drivers/ps2/keyboard.h>
#include <mem.h>
#include <lib/string.h>
#include <lib/mem.h>
#include <lib/elf.h>
#include <interrupts.h>

static void end_kernel_reading(void)
{
    // Those symbols are defined in the linker script
    extern char edata[], end[];

    // Filling the rest of the kernel with 0
    memset(edata, 0, end - edata);
}

void kernel_main(void)
{
    struct tty tty;
    extern char edata[], end[];

    end_kernel_reading();

    vga_clear();
    vga_print(0, 0, 0x0F, "Starting kernel...\n");
    init_tty(&tty, (struct tty_print_interface) {
        .clear          = vga_clear,
        .display_char   = vga_putc,
        .display_int    = vga_printn,
        .display_string = vga_print,
        .get_char       = vga_get_char,
    });

    idt_setup();
    init_ps2_keyboard();
    init_physical_memory(PHYS_MEM_START, PHYS_MEM_SIZE);
    launch_tty(&tty);
    for (;;);
}
