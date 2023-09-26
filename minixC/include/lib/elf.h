/**
 * @brief       This file contains everything needed to parse an ELF file.
*/

#ifndef __JL_ELF_H__
#define __JL_ELF_H__

#include <lib/types.h>

#define ELF_MAGIC_0 0x7F
#define ELF_MAGIC_1 'E'
#define ELF_MAGIC_2 'L'
#define ELF_MAGIC_3 'F'


/**
 * @brief   This is the schema of actual ELF files.
 * 
 * +--------------------------+ <- 0x0
 * |       Magic bytes        |
 * +--------------------------+ <- 0x4
 * |           Bits           |
 * +--------------------------+ <- 0x5
 * |          Unused          |
 * +--------------------------+ <- 0x18
 * |        Entry point       |
 * +--------------------------+ <- 0x1C
 * |   Program header offset  |
 * +--------------------------+ <- 0x20
 * |        Header off        |
 * +--------------------------+ <- 0x24
 * |          Unused          |
 * +--------------------------+ <- 0x28
 * |        Header size       |
 * +--------------------------+ <- 0x2A
 * |   PH table entry size    |
 * +--------------------------+ <- 0x2C
 * |        Nb entries        |
 * +--------------------------+ <- 0x2E
 * | Size Header Table entry  |
 * +--------------------------+ <- 0x30
 * |    Nb Section header     |
 * +--------------------------+ <- 0x32
 * |          Unused          |
 * +--------------------------+ <- 0x34
 * 
*/
struct elf_header {
    uint8_t magic[4];                       // Magic bytes 0x7F, 'E', 'L', 'F'
    uint8_t bits;                           // 1 for 32-bit, 2 for 64-bit
    uint8_t _1[19];                         // unused
    uint32_t entry_point;                   // Entry point of the kernel file
    uint32_t prgm_header_offset;            // Program Header offset, entry of all the program headers
    uint32_t section_header_offset;         // Offset of the section header table
    uint8_t _2[4];                          // unused
    uint16_t header_size;                   // Size of this header, 52 bytes for 32-bit, 64 bytes for 64-bit
    uint16_t prgm_header_tentry_size;       // Size of a program header table entry
    uint16_t nb_entries;                    // Number of entries in the program header table
    uint16_t section_header_tentry_size;    // Size of a section header table entry
    uint16_t nb_section_headers;            // Number of entries in the section header table
    uint8_t _3[2];                          // unused
} __attribute__((packed));

/**
 * @brief   Here is the program header structure and implementation, the total size
 * is: 32 bytes for 32 bits mode
 * +---------------+ <- 0x0
 * |     Unused    |
 * +---------------+ <- 0x04
 * |   Seg Offset  |
 * +---------------+ <- 0x08
 * |     Unused    |
 * +---------------+ <- 0x0C
 * | Physical addr |
 * +---------------+ <- 0x10
 * |     Unused    |
 * +---------------+ <- 0x14
 * |    Mem size   |
 * +---------------+ <- 0x18
 * |     Unused    |
 * +---------------+ <- 0x20
 * 
*/
struct elf_prgm_header {
    uint8_t _1[4];      // Unused
    uint32_t offset;    // Offset of the segment in the elf file
    uint8_t _2[4];      // Unused
    uint32_t phys_addr; // Physical addr of the program
    uint8_t _3[10];     // Unused
    uint32_t mem_size;  // Size of the segment
    uint8_t _4[2];      // Unused
};

typedef void (*elf_entry_point)();

/**
 * @brief           Check if a the file at given address is an ELF file or not
 * @param   addr    The address of the file
 * @return          1 if the file is an ELF file, 0 otherwise
*/
int is_elf(void *addr);

/**
 * @brief           Get the size of an elf file at given address
 * @param   addr    The address of the file
 * @return          The size of the file
*/
size_t elf_size(void *addr);

/**
 * @brief           Get the entry point of an elf file at given addr
 * @param   addr    The address of the file
 * @return          the function or null
*/
elf_entry_point get_elf_entry_point(void *addr);

/**
 * @brief           Check if the elf at given addr is 32 bits or 64 bits
 * @param   addr    The addr of the elf file
 * @param   mode    1 -> 32, 2 -> 64
 * @return          1 if true 0 if false
*/
int elf_bit_mode(void *addr, int mode);

/**
 * @brief           Read an nb of bytes at an offset to a physical addr
 * @param   pa      The physical addr where to write the bytes
 * @param   elf     The addr where the elf file is
 * @param   offset  The offset from the start of the elf file
 * @param   count   Numbers of bytes to write
 * @return          1 if success, 0 if failure
*/
int read_elf_segment(void *pa, size_t offset, size_t count);

#endif
