/**
 * @file    This file contains everything about the boot process. It contains function
 * prototypes, types, macros and everything needed to load the kernel into memory
*/

#ifndef __JL_BOOT_DISK_H__
#define __JL_BOOT_DISK_H__

#include "lib.h"

#define PIC_DISK_DATA       0x1F0
#define PIC_DISK_STATUS     0x1F7
#define PIC_DISK_SECTOR     0x1F2
#define PIC_DISK_LBA_LOW    0x1F3
#define PIC_DISK_LBA_MID    0x1F4
#define PIC_DISK_LBA_HIGH   0x1F5
#define PIC_DISK_DEVICE     0x1F6
#define PIC_DISK_CMD        0x1F7
#define PIC_DISK_READ       0x20
#define PIC_DISK_READY      1 << 6

/**
 * @brief           This function reads a sector from the disk and stores it in
 *                  the given address
 * @param   addr    The address where to store the sector
 * @param   lba     The LBA of the sector to read
*/
void read_sector(void *addr, uint32_t lba);

/**
 * @brief   Wait the disk to be ready
*/
void wait_disk(void);

#endif
