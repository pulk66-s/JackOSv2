#
# This file contains all the assembly code to load the GDT and switch to 32-bit
# mode.
#

switch_to_32:
    cli                 # disable interrupts
    lgdt gdt_descriptor # load GDT
    movl %cr0, %eax      # get current cr0
    orl $1, %eax         # set PE bit
    movl %eax, %cr0      # write back to cr0
    ljmp $0x08, $init32  # jump to 32-bit code

# GDT datastructure
.p2align 2  # force 4 byte alignment
gdt:
# NULL descriptor
    .word 0, 0
    .byte 0, 0, 0, 0

# Code descriptor
    .word 0xffff, 0
    .byte 0, 0x9a, 0xcf, 0

# Data descriptor
    .word 0xffff, 0
    .byte 0, 0x92, 0xcf, 0
gdt_end:

gdt_descriptor:
    .word gdt_end - gdt - 1
    .long gdt

# 32-bit entry point
.code32
init32:
    # Set up the protected-mode data segment registers
    movw $0x10, %ax # Our data segment selector
    movw %ax, %ds   # -> DS: Data Segment
    movw %ax, %es   # -> ES: Extra Segment
    movw %ax, %fs   # -> FS
    movw %ax, %gs   # -> GS
    movw %ax, %ss   # -> SS: Stack Segment

    # Set up the stack pointer and call into C.
    movl $_start, %esp
    call start_boot

.code16
