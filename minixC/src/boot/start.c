#include <include/boot.h>
#include <drivers/pic.h>
#include <boot.h>
#include <mem.h>

/**
 * @brief       Print a character on the screen to test the boot process
 * @param   c   The character to print
*/
static void print_char(char c, int x, int y)
{
    unsigned char *video = (unsigned char *)0xb8000;
    int offset = (y * 80 + x) * 2;

    video[offset] = c;
    video[offset + 1] = 0x0F;
}

/**
 * @brief       Print a string on the screen to test the boot process
 * @param   str The string to print
 * @param   x   The x position where to print the string
 * @param   y   The y position where to print the string
*/
static void print_str(char *str, int x, int y)
{
    for (int i = 0; str[i]; i++) {
        print_char(str[i], x + i, y);
    }
}

/**
 * @brief           Read all the sectors from the kernel to the given address
 * @param   addr    The address where to store the kernel
*/
void read_kernel(void *addr)
{
    read_sector(addr, CHS_TO_LBA(0, 0, 3));
}

void start_boot(void)
{
    print_str("START", 0, 0);
    read_kernel((void *)KERNEL_START);
    if (is_elf((void *)KERNEL_START)) {
        print_str("KERNEL IS ELF", 0, 1);
    } else {
        print_str("KERNEL IS NOT ELF", 0, 1);
    }
    print_str("END", 0, 2);
    for (;;);
}
