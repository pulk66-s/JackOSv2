/**
 * @file    This file contains everything from the memory management
 * but especially the GDT
*/

#ifndef __JL_MEM_GDT_H__
#define __JL_MEM_GDT_H__

/**
 * @brief   Here is the GDT Datatype schema
 * 
 * unit: bit
 * 0         64         128        192
 * +----------+----------+----------+----------+
 * | SEG_NULL | SEG_CODE | SEG_DATA |   ...    |
 * +----------+----------+----------+----------+
 * 
 * A Segment is 8 bytes long (64 bits) and looks like this
 *
 * - The first segment is the null segment, it is used to prevent the
 * processor from crashing when it tries to access a segment that
 * doesn't exist
 * 
 * - The second segment is the code segment, it is used to store the
 * code of the kernel
 * 
 * - The third segment is the data segment, it is used to store the
 * data of the kernel
 * 
 * +-------+--------------+
 * | 0-15  | Limit 1      |
 * +-------+--------------+
 * | 16-31 | Base 1       |
 * +-------+--------------+
 * | 32-39 | Base 2       |
 * +-------+--------------+
 * | 40-47 | Access Bytes |
 * +-------+--------------+
 * | 48-51 | Limit 2      |
 * +-------+--------------+
 * | 52-55 | Flags        |
 * +-------+--------------+
 * | 56-63 | Base 3       |
 * +-------+--------------+
 * 
 * The limit and the base are split into many parts because of the 32 bit,
 * This is because the limit is 20 bits long and the base is 32 bits long
 * The access bytes are split into 3 parts:
 *  - 1 byte for the access rights
 *  - 1 byte for the flags
 *  - 1 byte for the limit
*/

/**
 * @brief   This macros initializes the GDT in assembler
*/
#define GDT_SEG_NULL \
    .word 0, 0 \
    .byte 0, 0, 0, 0

/**
 * Here is the logic behind the GDT_SEG macro:
 * - the first word is the limit, it is 20 bits long so we have to shift it
 *   12 bits to the right to get the 16 first bits, then we mask it with 0xffff
 *   to get the 16 last bits
 * 
 * - the second word is the base, it is 32 bits long so we mask it with 0xffff
 *   to get the 16 first bits
 * 
 * - The first byte is the 8 last bits of the base shifted 16 bits to the right
 * 
 * - The second byte is the access byte, it is the flags ORed with 0x90
 *  (0x90 is the kernel code segment) 0x90 = 0b10010000
 *  the first bit is the present bit, it is set to 1, meaning that the segment
 *  is present in memory, the second bit is the privilege bit, it is set to 0
 *  to tell it's a kernel segment
 * 
 * - The third byte is the limit, it is the 4 last bits of the limit shifted
 *  28 bits to the right
 * 
 * - The fourth byte is the flags, it is the 4 last bits of the base shifted
 *  24 bits to the right
*/
#define GDT_SEG(flags, base, limit) \
    .word (((limit) >> 12) & 0xffff), ((base) & 0xffff); \
    .byte (((base) >> 16) & 0xff), (0x90 | (flags)), \
    (0xC0 | (((limit) >> 28) & 0xf)), (((base) >> 24) & 0xff)

/**
 * @brief   This is the flags used to set the gdt flags
*/

#define GDT_SEG_LONG_MODE       1 << 1  // 64 bit mode (32 bit without this flag)
#define GDT_SEG_SIZE_32         1 << 2  // 32 bit mode (16 bit without this flag)
#define GDT_SEG_GRANULARITY_4K  1 << 3  // 4K granularity (1K without this flag)

/**
 * @brief   This is the access byte used to set the gdt access byte
*/

#define SEG_EXECUTABLE  1 << 3  // Executable segment
#define SEG_WRITABLE    1 << 1	// Writable segment (non-executable segment)
#define SEG_READABLE    1 << 1  // Readable segment (executable segment)

#endif
