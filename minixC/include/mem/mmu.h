/**
 * @file    This file describe how the memory is managed by the kernel
*/

#ifndef __CL_MEM_MMU_H__
#define __CL_MEM_MMU_H__

/**
 * Actual memory map
 * +-----------------------+ <- 0x00
 * |       BootLoader      | BootLoader stuff
 * +-----------------------+ <- 0x7e00
 * |                       | Empty space for stack
 * +-----------------------+ <- 0x10000
 * |         Kernel        | Kernel code
 * +-----------------------+ <- 0x????
*/

#define KERNEL_START 0x10000

#define SECTOR_SIZE 512 // Minimum size of a memory move between hard drive and memory

/**
 * Convert the CHS address to a LBA address, the CHS address is the address of a sector on the hard drive
 * @param   c   The cylinder number
 * @param   h   The head number
 * @param   s   The sector number
 * 
 * The LBA address is the address of a sector on the hard drive 
*/
#define CHS_TO_LBA(c, h, s) ((c * 16 + h) * 63 + s - 1)

#endif