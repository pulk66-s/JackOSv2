#include <include/clib/string.h>
#include <include/clib/memory.h>
#include <include/console.h>
#include <include/graphics/CGA.h>

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
 * @brief   Initialize the i386 architecture
*/
void i386_init(void)
{
    end_elf_process();
    console_init(NULL);
    kcons_printc('!');
    kcons_prints("Hello, world!");
    kcons_printn(42);
    kcons_printc('!');
    for (;;);
}