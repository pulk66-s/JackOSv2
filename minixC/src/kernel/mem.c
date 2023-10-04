/**
 * @file    mem.c
 * @brief   Memory management functions for the kernel
*/

#include <mem/kernel.h>
#include <mem/mmu.h>
#include <drivers/vga.h>
#include <lib/math.h>

/**
 * @brief           This function allocate a memory block of given size
 * @param   size    The size of the memory block to allocate
 * @return          The address of the allocated memory block
 * !                This function will must be used before the kernel has setup
 * !                the memory management system.
 * !                This function will panic if there is no more memory available
*/
void *kmalloc(size_t size)
{
    static int init = 0, offset = 0;
    static void *page_ptr = NULL;
    void *block_ptr = NULL;
    extern char end[];  // Used to get the end of the kernel, defined in the linker script

    if (!init) {
        init = 1;
        page_ptr = (void *)(ROUNDUP((size_t)end, SECTOR_SIZE));
        vga_print(0, 1, 0x0F, "INIT");
    }
    block_ptr = page_ptr + offset;
    offset += size;
    if (offset >= SECTOR_SIZE * KMEM_DEFAULT_NB_PAGES) {
        vga_clear();
        vga_print(
            0, 0, 
            VGA_COLOR(VGA_COLOR_WHITE, VGA_COLOR_RED),
            "PANIC: No more memory available in kalloc\n"
        );
        for (;;);
    }
    return block_ptr;
}
