/**
 * @file    nvram.c
 * @brief   NVRAM command
 * 
 * @details
 * This file contains the NVRAM command implementation
 * ! This command works only on the kernel console
*/

#include <include/console.h>
#include <include/mem/nvram.h>

/**
 * @brief           Display the NVRAM
 * @param   argv    The arguments
*/
void nvram_cmd(char **argv) {
    struct nvram_info *nvram = nvram_get_info();

    kcons_printf("NVRAM informations:\n");
    kcons_prints("\tBase memory: ");
    kcons_printn(nvram->npages_basemem);
    kcons_prints(" pages \n");
    kcons_prints("\tExtended memory: ");
    kcons_printn(nvram->npages_extmem);
    kcons_prints(" pages \n");
}
