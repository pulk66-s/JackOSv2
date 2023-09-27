#include <include/boot.h>
#include <lib/elf.h>
#include <lib/string.h>
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
static void print_nb(long long nb, int x, int y)
{
    char str[32] = {0};

    itoa(nb, str, 10);
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

static void setup_first_kernel_sector(struct elf_header *elfh)
{
    struct elf_header relfh = *elfh;
    print_str("START", 0, 0);
    read_kernel_first_sector((void *)KERNEL_START);

    if (!is_elf((void *)elfh)) {
        print_str("NOT GOOD, KERNEL_START is not elf", 0, 1);
        for (;;);
    }
    if (!elf_bit_mode((void *)elfh, 1)) {
        print_str("NOT GOOD, kernel is not 32 bits", 0, 1);
        for (;;);
    }
    if ((size_t)(&relfh.prgm_header_offset) != (size_t)(&relfh) + 0x1C) {
        print_str("e_phoff wrong: ", 0, 1);
        for (;;);
    }
    // if (relfh.entry_point != 0xf0100000) {
    //     print_str("e_entry wrong: ", 0, 1);
    //     for (;;);
    // }
}

/**
 * @brief           Read an nb of bytes at an offset to a physical addr
 * @param   pa      The physical addr where to write the bytes
 * @param   offset  The offset from the start of the elf file
 * @param   count   Numbers of bytes to write
 * @return          1 if success, 0 if failure
*/
int read_elf_segment(void *pa, size_t offset, size_t count)
{
    uint32_t endpa = pa + count;

    endpa &= ~(SECTOR_SIZE - 1);           // Round down to sector boundary.
    offset = (offset / SECTOR_SIZE) + 1;   // Sector offset in kernel file.
    while (pa < endpa) {
        read_sector((void *)pa, offset);
        pa += SECTOR_SIZE;
        offset++;
    }
    return 1;
}

static void setup_kernel_programs(struct elf_header *elfh)
{
    struct elf_prgm_header *elfph = (struct elf_prgm_header *)((uint8_t *)(elfh) + elfh->prgm_header_offset);
    struct elf_prgm_header *eelfph = (struct elf_prgm_header *)(elfph + elfh->nb_entries);

    for (int i = 0; elfph < eelfph; elfph++, i++) {
        print_nb(i, 0, 2 + i);
        print_nb(elfph->phys_addr, 10, 2 + i);
        print_nb(elfph->offset, 20, 2 + i);
        print_nb(elfph->mem_size, 30, 2 + i);
        if (!read_elf_segment(elfph->phys_addr, elfph->offset, elfph->mem_size)) {
            print_str("Fail to read elf prgm segment: ", 0, 1);
        }
    }
}

void start_boot(void)
{
    struct elf_header *elfh = (struct elf_header *)KERNEL_START;
    elf_entry_point kstart = NULL;

    setup_first_kernel_sector(elfh);
    size_t elfph_offset = elfh->prgm_header_offset;
    setup_kernel_programs(elfh);

    kstart = (elf_entry_point)elfh->entry_point;
    print_str("Entering the kernel", 0, 8);
    print_nb(elfh->entry_point, 0, 9);
    kstart();
    print_str("End of the bootmain", 0, 10);
    for (;;);
}
