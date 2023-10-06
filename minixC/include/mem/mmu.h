/**
 * @file    This file describe how the memory is managed by the kernel
*/

#ifndef __CL_MEM_MMU_H__
#define __CL_MEM_MMU_H__

#include <lib/types.h>

// Define type to know what type of address we are using
typedef uint32_t phys_addr;
typedef uint32_t virt_addr;

/**
 * Actual memory map for physical memory
 * +-----------------------+ <- 0x00
 * |       BootLoader      | BootLoader stuff
 * +-----------------------+ <- 0x7e00
 * |                       | Empty space for stack
 * +-----------------------+ <- 0x10000
 * |         Kernel        | Kernel code
 * +-----------------------+ <- 0x1C800
 * | Physical memory mngmt | Physical memory manager
 * +-----------------------+ <- 0x1CC00
*/

#define KERNEL_PHYS_START   0x10000     // This is the kernel physical address, the bootloader will load the kernel at this address

// This is the size allowed of the kernel code, 100 sectors of 512 bytes
#define KERNEL_SIZE         0xC800

// This is the end of the kernel code, the bootloader will load the kernel at this address
#define KERNEL_PHYS_END     (KERNEL_PHYS_START + KERNEL_SIZE)

// This is the start of the physical memory for the physical memory manager
// the bootloader use the first 1MB of the memory
#define PHYS_MEM_START      KERNEL_PHYS_END

// The size of the physical memory for the physical memory manager
// 0x1000 = 4KB of physical memory
#define PHYS_MEM_SIZE       0x1000

// End of the physical memory for the physical memory manager
#define PHYS_MEM_END        (PHYS_MEM_START + PHYS_MEM_SIZE)

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
