/**
 * @file iso.h
 * @brief   this file contains the schema and the datas of the ISO image
*/

#ifndef __JL_ISO_H__
#define __JL_ISO_H__

/**
 * The address (0, 0, 0) is not used because it is the MBR (Master Boot Record)
 * +-------------+ <- 0x00, (C, H, S) = (0, 0, 1)
 * | BOOT Loader |
 * +-------------+ <- 0x600, (C, H, S) = (0, 0, 5)
 * | Kernel Code |
 * +-------------+
*/

#define BOOT_LOADER_SECTOR_BASE 1
#define BOOT_LOADER_SECTOR_SIZE 4
#define KERNEL_BASE_SECTOR      (BOOT_LOADER_SECTOR_SIZE + BOOT_LOADER_SECTOR_BASE)

#endif
