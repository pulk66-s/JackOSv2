#define	RELOC(x) ((x) - 0xF0000000)

.globl kernel_main

.globl _start
_start = RELOC(entry)

.globl entry
entry:
    call kernel_main
    ret
