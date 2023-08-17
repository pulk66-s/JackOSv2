/**
 * @file types.h
 * @brief The types definition.
 * 
 * @details
 * This file contains all the basic types definition that you need to use in the kernel.
*/

#ifndef __JOS_INCLUDE_TYPES_h__
#define __JOS_INCLUDE_TYPES_h__

#define ROUNDUP(a, sz)  (((uintptr_t)(a) + (sz) - 1) & ~((sz) - 1))

typedef char                int8_t;
typedef short               int16_t;
typedef int                 int32_t;
typedef long long           int64_t;
typedef unsigned char       uint8_t;
typedef unsigned short      uint16_t;
typedef unsigned int        uint32_t;
typedef unsigned long long  uint64_t;
typedef uint64_t            size_t;

#define NULL ((void *)0)

// pte_t is the type of a page table entry.
typedef uint32_t pte_t;
typedef uint32_t pde_t;

/**
 * Pointers and addresses are 32 bits long.
 * We use pointer types to represent virtual addresses,
 * uintptr_t to represent the numerical values of virtual addresses,
 * and physaddr_t to represent physical addresses.
*/
typedef int32_t     intptr_t;
typedef uint32_t    uintptr_t;
typedef uint32_t    physaddr_t;


#endif