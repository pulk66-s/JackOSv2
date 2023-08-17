/**
 * @file    nvram.c
 * @brief   Non-volatile RAM management
 * 
 * @details
 * This file contains the non-volatile RAM management code.
*/

#include <include/mem/nvram.h>
#include <include/x86.h>
#include <include/mmu.h>
#include <include/memlayout.h>
#include <include/console.h>

struct nvram_info nvram_info;
size_t nb_total_pages;

/**
 * @brief           Read from the non-volatile RAM
 * @param    reg    The register to read from
 * @return          The value of the register
 * ?? What is mc146818?
 *  * mc146818 is a chip that is used to read from the non-volatile RAM
*/
uint32_t mc146818_read(uint32_t reg)
{
    outb(IO_RTC, reg);
    return inb(IO_RTC + 1);
}


/**
 * @brief           Read from the non-volatile RAM
 * @param    reg    The register to read from
 * @return          The value of the register
*/
uint32_t nvram_read(uint32_t reg) {
	return mc146818_read(reg) | (mc146818_read(reg + 1) << 8);
}

/**
 * @brief           Init the nvram structure
*/
void nvram_init(void) {
	nvram_info.npages_basemem = (nvram_read(NVRAM_BASELO) * 1024) / PAGE_SIZE;
	nvram_info.npages_extmem = (nvram_read(NVRAM_EXTLO) * 1024) / PAGE_SIZE;

    if (nvram_info.npages_extmem) {
        nb_total_pages = (EXTPHYSMEM / PAGE_SIZE) + nvram_info.npages_extmem;
    } else {
        nb_total_pages = nvram_info.npages_basemem;
    }
    kcons_prints("nvram informations: \n");
    kcons_prints("nvram_info.npages_basemem: ");
    kcons_printn(nvram_info.npages_basemem);
    kcons_prints("\nnvram_info.npages_extmem: ");
    kcons_printn(nvram_info.npages_extmem);
    kcons_prints("\nnb_total_pages: ");
    kcons_printn(nb_total_pages);
    kcons_prints("\n\n");
}

/**
 * @brief           get the nvram informations
 * @return          The nvram_info struct filled
 * ! You need to call the "mem_init" function before calling this function
*/
struct nvram_info *nvram_get_info(void) {
    return &nvram_info;
}

/**
 * @brief           Get the amount of pages in the nvram
 * @return          The amount of pages in the nvram
*/
size_t get_nvram_nbpages(void) {
    return nb_total_pages;
}