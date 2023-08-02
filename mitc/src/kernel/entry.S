#include <include/mmu.h>
#include <include/memlayout.h>

.text
.globl _start

.globl entry
entry:
    call    i386_init

    # Should never get here, but in case we do, just spin.
spin:   jmp spin

