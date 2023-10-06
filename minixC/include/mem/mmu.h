/**
 * @file    This file describe how the memory is managed by the kernel
*/

#ifndef __CL_MEM_MMU_H__
#define __CL_MEM_MMU_H__

/**
 * Actual memory map for physical memory
 * +-----------------------+ <- 0x00
 * |       BootLoader      | BootLoader stuff
 * +-----------------------+ <- 0x7e00
 * |                       | Empty space for stack
 * +-----------------------+ <- 0x10000
 * |         Kernel        | Kernel code
 * +-----------------------+ <- 0x????
*/

#define KERNEL_PHYS_START   0x10000     // This is the kernel physical address, the bootloader will load the kernel at this address
#define KERNEL_CODE         0xF0000000  // This is the kernel code address, the kernel will be mapped at this address

#define SECTOR_SIZE 512 // Minimum size of a memory move between hard drive and memory

// This is the default number of pages that can be used before the kernel has setup 
// the memory management system
#define KMEM_DEFAULT_NB_PAGES   1

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
