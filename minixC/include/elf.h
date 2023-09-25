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
 * |   Unused    |
 * +-------------+ <- 0x34
*/
struct elf_header {
    uint8_t magic[4];                   // Magic bytes 0x7F, 'E', 'L', 'F'
    uint8_t bits;                       // 1 for 32-bit, 2 for 64-bit
    uint8_t _1[35];                     // unused
    uint16_t header_size;               // Size of this header, 52 bytes for 32-bit, 64 bytes for 64-bit
    uint16_t prgm_header_tentry_size;   // Size of a program header table entry
    uint8_t _2[8];                     // unused
} __attribute__((packed));

#endif
