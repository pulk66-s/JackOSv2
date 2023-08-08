/**
 * @file    init.c
 * @brief   Memory management initialization
 * 
 * @details
 * This file contains the memory management initialization code.
*/

#include <include/mem.h>
#include <include/mmu.h>
#include <include/console.h>

static struct nvram_info nvram_info;

/**
 * @brief   Initiate the memory management
*/
void mem_init(void) {
	nvram_info.npages_basemem = (nvram_read(NVRAM_BASELO) * 1024) / PAGE_SIZE;
	nvram_info.npages_extmem = (nvram_read(NVRAM_EXTLO) * 1024) / PAGE_SIZE;
}

/**
 * @brief           get the nvram informations
 * @return          The nvram_info struct filled
 * ! You need to call the "mem_init" function before calling this function
*/
struct nvram_info *nvram_get_info(void) {
    return &nvram_info;
}
