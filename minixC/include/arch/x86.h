#ifndef __JOS_ARCH_X86_H__
#define __JOS_ARCH_X86_H__

#include <lib/types.h>

struct registers {
    uint32_t ds;
    uint32_t edi, esi, ebp, useless, ebx, edx, ecx, eax;
    uint32_t interrupt, error;
    uint32_t eip, cs, eflags, esp, ss;
} __attribute__((packed));

#endif
