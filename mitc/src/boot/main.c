/**
 * @file main.c
 * @brief The main function of the boot system.
 * @details
 * This file contains the main function of the boot system. It start with C code
 * and then call the C code.
 * The goal of this file is to load the ELF kernel into the memory and then jump to
 * the kernel.
*/

#include <include/elf.h>
#include <include/x86.h>

#define SECTSIZE    512
#define ELFHDR      ((struct Elf *) 0x10000)    // scratch space

/**
 * @brief   This function wait for the disk to be ready.
*/
void waitDisk(void) {
    // wait for disk reaady
    while ((inb(0x1F7) & 0xC0) != 0x40) {
        // do nothing
    }
}

/**
 * @brief   This function read a sector from the kernel file and write it at the
 * destination address.
 * @param dst The destination address where to write the data.
 * @param offset The offset in the kernel file.
*/
void readSector(void *dst, uint32_t offset) {
    waitDisk();

    outb(0x1F2, 1);             // count = 1
    outb(0x1F3, offset);
    outb(0x1F4, offset >> 8);
    outb(0x1F5, offset >> 16);
    outb(0x1F6, (offset >> 24) | 0xE0);
    outb(0x1F7, 0x20);          // cmd 0x20 - read sectors

    // wait for disk to be ready
    waitDisk();

    // read a sector
    insl(0x1F0, dst, SECTSIZE/4);
}

/**
 * @brief   This function read 'count' bytes at 'offset' from the kernel into 
 * the physical address 'pa'.
 * @param pa The physical address where to write the data.
 * @param offset The offset in the kernel file.
 * @param count The number of bytes to read.
*/
void readSegment(uint32_t pa, uint32_t count, uint32_t offset) {
    uint32_t endpa = pa + count;

    endpa &= ~(SECTSIZE - 1);           // Round down to sector boundary.
    offset = (offset / SECTSIZE) + 1;   // Sector offset in kernel file.
    while (pa < endpa) {
        readSector((void *)pa, offset);
        pa += SECTSIZE;
        offset++;
    }
}

/**
 * @brief The main function of the boot system.
*/
void bootmain(void) {
    struct ProgramHeader *prgmHeader, *endPrgmHeader;

    readSegment((uint32_t) ELFHDR, SECTSIZE * 8, 0);
    if (ELFHDR->e_magic != ELF_MAGIC) {
        // The ELF header is not correct
        return;
    }
    prgmHeader = (struct ProgramHeader *) ((uint8_t *) ELFHDR + ELFHDR->e_phoff);
    endPrgmHeader = prgmHeader + ELFHDR->e_phnum;
    for (; prgmHeader < endPrgmHeader; prgmHeader++) {
        readSegment(prgmHeader->paddr, prgmHeader->memsz, prgmHeader->offset);
    }
    ((void (*)(void)) (ELFHDR->e_entry))();
    for (;;);
}
