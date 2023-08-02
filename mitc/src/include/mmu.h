#ifndef __JOS_INCLUDE_MMU_h__
#define __JOS_INCLUDE_MMU_h__

/*
 * @file mmu.h
 * @brief Memory management unit
 * @details
 * Memory management unit is responsible for managing the memory of the system.
 * It includes every memory related operations
 */

/*
 * This is GDT Definition and macros
 */

#ifdef __ASSEMBLER__	// Check if we are in GAS
#define SEG_NULL \
	.word 0, 0;  \
	.byte 0, 0, 0, 0
#define SEG(type, base, lim)                        \
	.word(((lim) >> 12) & 0xffff), ((base)&0xffff); \
	.byte(((base) >> 16) & 0xff), (0x90 | (type)),  \
		(0xC0 | (((lim) >> 28) & 0xf)), (((base) >> 24) & 0xff)
#endif

#define SEG_EXECUTABLE 0x8	// Executable segment
#define SEG_WRITABLE 0x2	// Writable segment (non-executable segment)
#define SEG_READABLE 0x2	// Readable segment (executable segment)

#endif