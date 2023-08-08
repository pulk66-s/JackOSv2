/**
 * @file    nvram.h
 * @brief   Non-volatile RAM management
 * 
 * @details
 * This file contains the non-volatile RAM management functions.
*/

#ifndef __JOS_INCLUDE_MEM_NVRAM_H__
#define __JOS_INCLUDE_MEM_NVRAM_H__

#include <include/types.h>

/**
 * Input Output RTC Port
 * ? What is RTC?
 *  * RTFM: https://en.wikipedia.org/wiki/Real-time_clock
*/
#define IO_RTC          0x070

#define MC_NVRAM_START  0xe  /* start of NVRAM: offset 14 */
#define NVRAM_BASELO    (MC_NVRAM_START + 7)    /* low byte; RTC off. 0x15 */
#define NVRAM_EXTLO     (MC_NVRAM_START + 9)    /* low byte; RTC off. 0x17 */

struct nvram_info {
    uint32_t npages_basemem;    /* base memory (KB) */
    uint32_t npages_extmem;     /* extended memory (KB) */
};

/**
 * @brief           Read from the non-volatile RAM
 * @param    reg    The register to read from
 * @return          The value of the register
*/
uint32_t nvram_read(uint32_t reg);

/**
 * @brief           Read from the non-volatile RAM
 * @param    reg    The register to read from
 * @return          The value of the register
 * ?? What is mc146818?
 *  * mc146818 is a chip that is used to read from the non-volatile RAM
*/
uint32_t mc146818_read(uint32_t reg);

/**
 * @brief           get the nvram informations
 * @param    info   The nvram_info struct to fill
 * @return          The nvram_info struct filled
 * ! You need to call the "mem_init" function before calling this function
*/
struct nvram_info *nvram_get_info(void);

#endif