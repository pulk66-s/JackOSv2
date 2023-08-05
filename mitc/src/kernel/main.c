#include <include/clib/string.h>
#include <include/clib/memory.h>
#include <include/console.h>
#include <include/graphics/CGA.h>
#include <include/graphics/serial.h>

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
    serial_init();
    console_init(NULL);
}

/**
 * @brief   Initialize the i386 architecture
*/
void i386_init(void)
{
    end_elf_process();
    initialize_kernel();
    kcons_prints("Welcome to JOS Kernel !!!\n");
    kcons_prints("JOS is now running...\n");
    for (;;);
}