/**
 * @file elf.h
 * @brief The ELF headers.
 * 
 * @details
 * This file contains all the ELF headers and definition that you need to load an
 * ELF file into the memory.
 * 
 * ? What is an ELF file?
 *  * RTFM: https://en.wikipedia.org/wiki/Executable_and_Linkable_Format
*/

#ifndef __JOS_INCLUDE_ELF_h__
#define __JOS_INCLUDE_ELF_h__

#include "types.h"

#define ELF_MAGIC 0x464C457FU   // "\x7FELF" in little endian

/**
 * @brief This is the structure that represents the program header.
 * The program header is a table that describe how to create a process image.
*/
struct ProgramHeader {
    uint32_t type;      // The type of the segment
    uint32_t offset;    // The offset of the segment in the file image
    uint32_t vaddr;     // The virtual address of the segment in memory
    uint32_t paddr;     // The physical address of the segment in memory
    uint32_t filesz;    // The size of the segment in the file image
    uint32_t memsz;     // The size of the segment in memory
    uint32_t flags;     // The flags of the segment
    uint32_t align;     // The alignment of the segment
};

struct Elf {
	uint32_t e_magic;	// must equal ELF_MAGIC
	uint8_t e_elf[12];
	uint16_t e_type;
	uint16_t e_machine;
	uint32_t e_version;
	uint32_t e_entry;
	uint32_t e_phoff;
	uint32_t e_shoff;
	uint32_t e_flags;
	uint16_t e_ehsize;
	uint16_t e_phentsize;
	uint16_t e_phnum;
	uint16_t e_shentsize;
	uint16_t e_shnum;
	uint16_t e_shstrndx;
};

#endif