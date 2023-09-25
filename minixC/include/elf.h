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
 * +-------------+ <- 0x0
 * | Magic bytes |
 * +-------------+ <- 0x4
 * |   Unused    |
 * +-------------+ <- 0x28
 * | Header size |
 * +-------------+ <- 0x2A
 * |  Entry size |
 * +-------------+ <- 0x2C
 * | # of entries|
 * +-------------+ <- 0x2E
 * |  Entry size |
 * +-------------+ <- 0x30
 * | # of entries|
 * +-------------+ <- 0x32
 * |   Unused    |
 * +-------------+ <- 0x34
*/
struct elf_header {
    uint8_t magic[4];                       // Magic bytes 0x7F, 'E', 'L', 'F'
    uint8_t bits;                           // 1 for 32-bit, 2 for 64-bit
    uint8_t _1[27];                         // unused
    uint32_t section_header_offset;         // Offset of the section header table
    uint32_t flags;                         // Flags
    uint16_t header_size;                   // Size of this header, 52 bytes for 32-bit, 64 bytes for 64-bit
    uint16_t prgm_header_tentry_size;       // Size of a program header table entry
    uint16_t nb_entries;                    // Number of entries in the program header table
    uint16_t section_header_tentry_size;    // Size of a section header table entry
    uint16_t nb_section_headers;            // Number of entries in the section header table
    uint8_t _2[2];                          // unused
} __attribute__((packed));

#endif
