#include <lib/elf.h>
#include <lib/mem.h>

/**
 * @brief           Check if a the file at given address is an ELF file or not
 * @param   addr    The address of the file
 * @return          1 if the file is an ELF file, 0 otherwise
*/
int is_elf(void *addr)
{
    uint8_t *buff = (uint8_t *)addr;

    return buff[0] == 0x7F && buff[1] == 'E' && buff[2] == 'L' && buff[3] == 'F';
}

/**
 * @brief           Get the size of an elf file at given address
 * @param   addr    The address of the file
 * @return          The size of the file
*/
size_t elf_size(void *addr)
{
    struct elf_header *elfh;

    if (!is_elf(addr))
        return 0;
    elfh = (struct elf_header *)addr;
    return elfh->section_header_offset + (elfh->section_header_tentry_size * elfh->nb_section_headers);
}

/**
 * @brief           Get the entry point of an elf file at given addr
 * @param   addr    The address of the file
 * @return          the function or null
*/
elf_entry_point get_elf_entry_point(void *addr)
{
    struct elf_header *elfh = (struct elf_header *)addr;

    if (!is_elf(addr))
        return NULL;
    return (elf_entry_point)elfh->entry_point;
}

/**
 * @brief           Check if the elf at given addr is 32 bits or 64 bits
 * @param   addr    The addr of the elf file
 * @param   mode    1 -> 32, 2 -> 64
 * @return          1 if true 0 if false
*/
int elf_bit_mode(void *addr, int mode)
{
    struct elf_header *elfh = (struct elf_header *)addr;

    if (mode != 1 && mode != 2)
        return 0;
    return elfh->bits == mode;
}
