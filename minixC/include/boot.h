/**
 * @file, This file contains everything about the boot process. It contains function
 * prototypes, types, macros and everything needed
*/

#ifndef __JL_BOOT_H__
#define __JL_BOOT_H__

#include "mem.h"

// Defined in boot/a20.S
extern void enable_a20(void);
extern int check_a20(void);

// Defined in boot/print.S
extern void print_char_16(char c);

void start_boot(void);
void switch_to_32(void);

#endif
