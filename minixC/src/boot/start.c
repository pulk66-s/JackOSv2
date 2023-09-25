#include <include/boot.h>
#include <elf.h>
#include <drivers/pic.h>
#include <boot.h>
#include <mem.h>
#include <iso.h>

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
 * @brief       Print a number on the screen to test the boot process
 * @param   n   The number to print
 * @param   x   The x position where to print the number
 * @param   y   The y position where to print the number
*/
static void print_nb(int nb, int x, int y)
{
    char str[32] = {0};
    size_t size = 0;

    while (nb > 0) {
        str[size++] = nb % 10 + '0';
        nb /= 10;
    }
    for (int i = 0; i < size / 2; i++) {
        char tmp = str[i];
        str[i] = str[size - i - 1];
        str[size - i - 1] = tmp;
    }
    print_str(str, x, y);
}

/**
 * @brief           Read all the sectors from the kernel to the given address
 * @param   addr    The address where to store the kernel
*/
void read_kernel_first_sector(void *addr)
{
    read_sector(addr, CHS_TO_LBA(0, 0, KERNEL_BASE_SECTOR));
}

/**
 * @brief           Read all the kernel sectors to the given address
 * @param   addr    The address where to store the kernel
 * @param   nb      The number of sectors to read
*/
void read_kernel(void *addr, size_t nb)
{
    for (size_t i = 0; i < nb; i++) {
        // i + 1, because the first sector is already read
        read_sector(addr + (i + 1) * SECTOR_SIZE, CHS_TO_LBA(0, 0, KERNEL_BASE_SECTOR + i + 1));
    }
}

void start_boot(void)
{
    print_str("START", 0, 0);
    read_kernel_first_sector((void *)KERNEL_START);
    if (is_elf((void *)KERNEL_START)) {
        print_str("KERNEL IS ELF", 0, 1);
    } else {
        print_str("KERNEL IS NOT ELF", 0, 1);
    }
    if (sizeof(struct elf_header) == 52) {
        print_str("ELF HEADER SIZE OK", 0, 2);
    } else {
        print_str("ELF HEADER SIZE NOT OK", 0, 2);
    }

    struct elf_header *elfh = (struct elf_header *)KERNEL_START;

    if (elfh->bits == 1) {
        print_str("ELF 32 BITS", 0, 3);
    } else {
        print_str("ELF 64 BITS", 0, 3);
    }
    if (&(elfh->header_size) == (void *)KERNEL_START + 0x28) {
        print_str("ELF STRUCT HEADER SIZE IS IN THE GOOD ADDRESS", 0, 4);
    } else {
        print_str("ELF STRUCT HEADER SIZE IS NOT IN THE GOOD ADDRESS", 0, 4);
    }
    if (elfh->header_size == 52) {
        print_str("ELF STRUCT HEADER SIZE IS OK", 0, 5);
    } else {
        print_str("ELF STRUCT HEADER SIZE IS NOT OK", 0, 5);
    }
    
    size_t file_size = elfh->section_header_offset + (elfh->section_header_tentry_size * elfh->nb_section_headers);
    size_t nb_sectors_to_read = file_size % SECTOR_SIZE == 0 ? file_size / SECTOR_SIZE - 1 : file_size / SECTOR_SIZE;

    read_kernel((void *)KERNEL_START, nb_sectors_to_read);

    if (is_elf((void *)KERNEL_START)) {
        print_str("KERNEL IS ELF", 0, 6);
    } else {
        print_str("KERNEL IS NOT ELF", 0, 6);
    }
    print_nb(file_size, 0, 7);
    print_nb(nb_sectors_to_read, 0, 8);
    print_str("END", 0, 9);
    for (;;);
}
