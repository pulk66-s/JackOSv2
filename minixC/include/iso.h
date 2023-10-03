/**
 * @file iso.h
 * @brief   this file contains the schema and the datas of the ISO image
*/

#ifndef __JL_ISO_H__
#define __JL_ISO_H__

/**
 * +---------------+ <- (C, H, S) = (0, 0, 0)
 * | BOOT Loader   |
 * +---------------+ <- (C, H, S) = (0, 0, 7)
 * | Kernel Header |
 * +---------------+ <- (C, H, S) = (0, 0, 15)
 * | Kernel Seg  1 |
 * +---------------+ <- (C, H, S) = (0, 0, 50)
 * | ............. |
 * +---------------+ <- (C, H, S) = (0, 0, 55)
 * | Kernel Seg  2 |
 * +---------------+ <- (C, H, S) = (0, 0, 60)
 * 
 *****************************************************
 * Here is the repartition of the kernel code in the ISO
 * The kernel code is stored in an elf 32 bits file.
 * 
 * Here is the actual readelf -l output of the kernel.elf (28/09/2023)
 * Program Headers:                                                             
 * Type           Offset   VirtAddr   PhysAddr   FileSiz MemSiz  Flg Align    
 * LOAD           0x001000 0xf0100000 0x00100000 0x01e61 0x01e61 R E 0x1000
 * 
 * We can see that the kernel is at the offset 0x001000 in the file
 * 0x1000 = 4096 bytes = 8 sectors. So we have a schema that looks like this
 * 
 * And the memory size is actually 0x01e61 (MemSiz) = 7777 bytes = 15.18 sectors -> 16 sectors
 * 
 * +------------+ <- (C, H, S) = (0, 0, 8)
 * | Elf Header |
 * +------------+ <- (C, H, S) = (0, 0, 9)
 * | Elf Unused |
 * +------------+ <- (C, H, S) = (0, 0, 16)
 * | Elf Text   |
 * +------------+ <- (C, H, S) = (0, 0, 32)
 * 
*/

#define BOOT_LOADER_SECTOR_BASE 1
#define BOOT_LOADER_SECTOR_SIZE 7
#define KERNEL_BASE_SECTOR      (BOOT_LOADER_SECTOR_SIZE + BOOT_LOADER_SECTOR_BASE)

#endif
