#include <boot/disk.h>
#include <drivers/pic.h>
#include <mem.h>

/**
 * @brief   This function reads a sector from the disk and stores it in the given
 *          address
 * @param   addr    The address where to store the sector
 * @param   lba     The LBA of the sector to read
*/
void read_sector(void *addr, uint32_t lba)
{
    wait_disk();

    // Setup the disk to read the sector
    pic_write(PIC_DISK_SECTOR, 1);
    pic_write(PIC_DISK_LBA_LOW, lba);
    pic_write(PIC_DISK_LBA_MID, lba >> 8);
    pic_write(PIC_DISK_LBA_HIGH, lba >> 16);
    pic_write(PIC_DISK_DEVICE, 0xE0 | (lba >> 24));

    // Read the sector
    pic_write(PIC_DISK_CMD, PIC_DISK_READ);

    wait_disk();

    pic_read_bytes(PIC_DISK_DATA, addr, SECTOR_SIZE / 4);
    // ? Why / 4 -> Because we read 4 bytes at a time
}

/**
 * @brief   Wait the disk to be ready
*/
void wait_disk(void)
{
    while ((pic_read(PIC_DISK_STATUS) & 0xC0) != PIC_DISK_READY);
}

/**
 * @brief           Check if a the file at given address is an ELF file or not
 * @param   addr    The address of the file
 * @return          1 if the file is an ELF file, 0 otherwise
*/
int is_elf(void *addr)
{
    uint8_t *buff = (uint8_t *)addr;

    return buff[0] == 0x7F && buff[1] == 'E' && buff[2] == 'L' && buff[3] == 'F';
}
