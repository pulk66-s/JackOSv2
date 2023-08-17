/**
 * @file    memlayout.h
 * @brief   Memory layout
 * 
 * @details
 * This file handles all the memory description and layout of the MIT C project 
*/

#ifndef __JOS_INCLUDE_MEMLAYOUT_H__
#define __JOS_INCLUDE_MEMLAYOUT_H__

/*
 * This file contains definitions for memory management in our OS,
 * which are relevant to both the kernel and user-mode software.
 */

// Global descriptor numbers
#define GD_KT     0x08     // kernel text
#define GD_KD     0x10     // kernel data
#define GD_UT     0x18     // user text
#define GD_UD     0x20     // user data
#define GD_TSS0   0x28     // Task segment selector for CPU 0

/*
 * Virtual memory map:                                Permissions
 *                                                    kernel/user
 *
 *    4 Gig -------->  +------------------------------+
 *                     |                              | RW/--
 *                     ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *                     :              .               :
 *                     :              .               :
 *                     :              .               :
 *                     |~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~| RW/--
 *                     |                              | RW/--
 *                     |   Remapped Physical Memory   | RW/--
 *                     |                              | RW/--
 *    KERNEL_BASE, ---->  +------------------------------+ 0xf0000000      --+
 *    KSTACKTOP        |     CPU0's Kernel Stack      | RW/--  KSTKSIZE   |
 *                     | - - - - - - - - - - - - - - -|                   |
 *                     |      Invalid Memory (*)      | --/--  KSTKGAP    |
 *                     +------------------------------+                   |
 *                     |     CPU1's Kernel Stack      | RW/--  KSTKSIZE   |
 *                     | - - - - - - - - - - - - - - -|                 PAGE_TABLE_SIZE
 *                     |      Invalid Memory (*)      | --/--  KSTKGAP    |
 *                     +------------------------------+                   |
 *                     :              .               :                   |
 *                     :              .               :                   |
 *    MMIOLIM ------>  +------------------------------+ 0xefc00000      --+
 *                     |       Memory-mapped I/O      | RW/--  PAGE_TABLE_SIZE
 * ULIM, MMIOBASE -->  +------------------------------+ 0xef800000
 *                     |  Cur. Page Table (User R-)   | R-/R-  PAGE_TABLE_SIZE
 *    UVPT      ---->  +------------------------------+ 0xef400000
 *                     |          RO PAGES            | R-/R-  PAGE_TABLE_SIZE
 *    UPAGES    ---->  +------------------------------+ 0xef000000
 *                     |           RO ENVS            | R-/R-  PAGE_TABLE_SIZE
 * UTOP,UENVS ------>  +------------------------------+ 0xeec00000
 * UXSTACKTOP -/       |     User Exception Stack     | RW/RW  PGSIZE
 *                     +------------------------------+ 0xeebff000
 *                     |       Empty Memory (*)       | --/--  PGSIZE
 *    USTACKTOP  --->  +------------------------------+ 0xeebfe000
 *                     |      Normal User Stack       | RW/RW  PGSIZE
 *                     +------------------------------+ 0xeebfd000
 *                     |                              |
 *                     |                              |
 *                     ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *                     .                              .
 *                     .                              .
 *                     .                              .
 *                     |~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|
 *                     |     Program Data & Heap      |
 *    UTEXT -------->  +------------------------------+ 0x00800000
 *    PFTEMP ------->  |       Empty Memory (*)       |        PAGE_TABLE_SIZE
 *                     |                              |
 *    UTEMP -------->  +------------------------------+ 0x00400000      --+
 *                     |       Empty Memory (*)       |                   |
 *                     | - - - - - - - - - - - - - - -|                   |
 *                     |  User STAB Data (optional)   |                 PAGE_TABLE_SIZE
 *    USTABDATA ---->  +------------------------------+ 0x00200000        |
 *                     |       Empty Memory (*)       |                   |
 *    0 ------------>  +------------------------------+                 --+
 *
 * (*) Note: The kernel ensures that "Invalid Memory" is *never* mapped.
 *     "Empty Memory" is normally unmapped, but user programs may map pages
 *     there if desired.  JOS user programs map pages temporarily at UTEMP.
 */


// All physical memory mapped at this address
#define	KERNEL_BASE	0xF0000000

// At IOPHYSMEM (640K) there is a 384K hole for I/O.  From the kernel,
// IOPHYSMEM can be addressed at KERNEL_BASE + IOPHYSMEM.  The hole ends
// at physical address EXTPHYSMEM.
#define IOPHYSMEM	0x0A0000
#define EXTPHYSMEM	0x100000

// Kernel stack.
#define KSTACKTOP	KERNEL_BASE
#define KSTKSIZE	(8*PAGE_SIZE)   		// size of a kernel stack
#define KSTKGAP		(8*PGSIZE)   		// size of a kernel stack guard

// Memory-mapped IO.
#define MMIOLIM		(KSTACKTOP - PAGE_TABLE_SIZE)   // Memory-mapped Input / Output limit
#define MMIOBASE	(MMIOLIM - PAGE_TABLE_SIZE)     // Memory-mapped Input / Output base

#define ULIM		(MMIOBASE)          // User Limit

/*
 * User read-only mappings! Anything below here til UTOP are readonly to user.
 * They are global pages mapped in at env allocation time.
 */

// User read-only virtual page table (see 'uvpt' below)
#define USER_VIRT_PAGE_ADDR		(ULIM - PAGE_TABLE_SIZE)
// Read-only copies of the Page structures
#define UPAGES		            (USER_VIRT_PAGE_ADDR - PAGE_TABLE_SIZE)
// Read-only copies of the global env structures
#define UENVS		            (UPAGES - PAGE_TABLE_SIZE)

/*
 * Top of user VM. User can manipulate VA from UTOP-1 and down!
 */

// Top of user-accessible VM
#define UTOP		UENVS
// Top of one-page user exception stack
#define UXSTACKTOP	UTOP
// Next page left invalid to guard against exception stack overflow; then:
// Top of normal user stack
#define USTACKTOP	(UTOP - 2*PGSIZE)

// Where user programs generally begin
#define UTEXT		(2*PAGE_TABLE_SIZE)

// Used for temporary page mappings.  Typed 'void*' for convenience
#define UTEMP		((void*) PAGE_TABLE_SIZE)
// Used for temporary page mappings for the user page-fault handler
// (should not conflict with other temporary page mappings)
#define PFTEMP		(UTEMP + PAGE_TABLE_SIZE - PGSIZE)
// The location of the user-level STABS data structure
#define USTABDATA	(PAGE_TABLE_SIZE / 2)


#endif