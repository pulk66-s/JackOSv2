#include <include/clib/string.h>
#include <include/clib/memory.h>
#include <include/console.h>
#include <include/graphics/CGA.h>
#include <include/graphics/serial.h>

static struct console_interface serial_interface = {
    .putc = serial_putc,
    .puts = serial_puts,
    .putn = serial_putn,
    .clear = serial_clear,
    .printf = serial_printf
};


/**
 * @brief   End the ELF loading process
*/
static inline void end_elf_process(void)
{
    extern char edata[], end[];

    // Before doing anything else, complete the ELF loading process.
    // Clear the uninitialized global data (BSS) section of our program.
    // This ensures that all static/global variables start out zero.
    memset(edata, 0, end - edata);
}

/**
 * @brief   Initialize everything
*/
static inline void initialize_kernel(void) {
    cga_init();
    console_init(NULL);
    if (!serial_init()) {
        cga_puts("Serial port doesn't exist\n", 0, 0, CGA_COLOR(CGA_COLOR_RED, CGA_COLOR_BLACK));
    } else {
        console_add_interface(&serial_interface);
    }
}

/**
 * @brief   Initialize the i386 architecture
*/
void i386_init(void)
{
    end_elf_process();
    initialize_kernel();
    kcons_prints("Welcome to JOS Kernel !!!\n");
    // kcons_prints("JOS is now running...\n");
    for (;;);
}
