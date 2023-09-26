#define	RELOC(x) ((x) - 0xF0000000)

.globl _start
.globl kernel_main
_start = RELOC(entry)

entry:
    call kernel_main
