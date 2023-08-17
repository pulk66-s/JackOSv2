#ifndef __JOS_INCLUDE_PMAP_H__
#define __JOS_INCLUDE_PMAP_H__

#include "types.h"
#include "memlayout.h"
#include "console.h"

/* This macro takes a kernel virtual address -- an address that points above
 * KERNEL_BASE, where the machine's maximum 256MB of physical memory is mapped --
 * and returns the corresponding physical address.  It panics if you pass it a
 * non-kernel virtual address.
 */
#define PHYS_ADDR(kva) _paddr(kva)

static inline physaddr_t
_paddr(void *kva)
{
	if ((uint32_t)kva < KERNEL_BASE)
        panic("PANIC");
	return (physaddr_t)kva - KERNEL_BASE;
}

#endif