.code16

/**
 *
 * This is the current GDT structure,
 * It's a 32-bit structure, so it's a 3 * 8 bytes long.
 * The GDT is essential for memory management. It's a table of segments.
 * That tells the CPU what memory is available and what is not.
 * The structure of this GDT is as follows:
 * 3 entry of 8 bytes each.
 * - gdt_null: The null segment, it's a segment that is not used. It's a mandatory
 *             segment, so it's always present.
 * - gdt_code: The code segment, it's a segment that contains the code of the kernel.
 * - gdt_data: The data segment, it's a segment that contains the data of the kernel.
 *             It's the same as code segment except for the type flags
 *
 * What is a segment ?
 *      A segment is a part of the memory that is accessible by the CPU.
 *      In 32-bit mode, the CPU can access 4GB of memory, but it's not enough.
 *      4GB = 4 * 1024 * 1024 * 1024 = 4 294 967 296 bytes = 2 ** 32 (32 bits max addressable)
 * Why 32 bits is not enough ?
 *      Because the kernel is not the only program that is running on the computer.
 *      There is also the BIOS, the bootloader, and the user programs.
 *      So the kernel is not the only program that needs memory.
 * What is the solution ?
 *      Go to 64 bits mode.
 *
 * Each segment is 8 bytes long, and is structured as follows:
 * - 0-15: The limit of the segment, it's the size of the segment.
 * - 16-31: The base of the segment, it's the address of the segment. Two first bytes of the address.
 * - 32-39: The base of the segment, it's the address of the segment. Third byte of the address.
 * - 40-47: The type of the segment, it's the type of the segment.
 * - 48-51: The flags of the segment, it's the flags of the segment.
 *  – Code: 1 for code, since this is a code segment
 *  – Conforming: 0, by not corming it means code in a segment with a lower privilege 
 *    may not call code in this segment - this a key to memory protection
 *  – Readable: 1, 1 if readible, 0 if execute-only. Readible allows us to read
 *    constants defined in the code.
 *  – Accessed: 0 This is often used for debugging and virtual memory techniques,
 *    since the CPU sets the bit when it accesses the segment
 *  - Others...
 * - 52-55: The limit of the segment, it's the size of the segment.
 */

gdt_start:

gdt_null:
    .byte 0x00, 0x00, 0x00, 0x00
    .byte 0x00, 0x00, 0x00, 0x00

gdt_code:
    # Limit of the segment, 0xFFFF = 65535 bytes is the maximum size of a segment
    .word 0xFFFF
    # Base of the segment, 0x0000 = 0 is the base address of the segment, 3 first bytes
    .word 0x0000
    .byte 0x00
    # flags of the segment
    .byte 1, 0, 0, 1, 1, 0, 1, 0
    .byte 1, 1, 0, 0, 1, 1, 1, 1
    # Base of the segment, 0x0000 = 0 is the base address of the segment last byte
    .byte 0x00

gdt_data:
    # Limit of the segment, 0xFFFF = 65535 bytes is the maximum size of a segment
    .word 0xFFFF
    # Base of the segment, 0x0000 = 0 is the base address of the segment, 3 first bytes
    .word 0x0000
    .byte 0x00
    # flags of the segment
    .byte 1, 0, 0, 1, 0, 0, 1, 0
    .byte 1, 1, 0, 0, 1, 1, 1, 1
    # Base of the segment, 0x0000 = 0 is the base address of the segment last byte
    .byte 0x00

gdt_end:

/**
 *
 * This is the current GDT descriptor.
 * A descriptor is a 48-bit structure that describes a structure
 * It contains the address of the structure and its size.
 * The structure of this descriptor is as follows:
 * - 6 bytes: The size of the GDT, 3 * 8 bytes
 * - 6 bytes: The address of the GDT, the label gdt_start
 *
 */
gdt_descriptor:
    # Size of the GDT, 3 * 8 bytes
    .word gdt_end - gdt_start - 1
    # Address of the GDT, the label gdt_start
    .long gdt_start

CODE_SEG = gdt_code - gdt_start
DATA_SEG = gdt_data - gdt_start
