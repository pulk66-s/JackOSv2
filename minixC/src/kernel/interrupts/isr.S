.globl isr_handler
.globl irq_handler

isr_common:
    pusha

    xorl %eax, %eax
    movl %ds, %eax
    pushl %eax

    movl $0x10, %eax
    mov %ax, %ds
    mov %ax, %es
    mov %ax, %fs
    mov %ax, %gs

    pushl %esp
    call isr_handler
    add $0x4, %esp

    popl %eax
    mov %ax, %ds
    mov %ax, %es
    mov %ax, %fs
    mov %ax, %gs

    popa
    add $0x8, %esp
    sti
    iret

irq_common:
    pusha

    xorl %eax, %eax
    movl %ds, %eax
    pushl %eax

    movl $0x10, %eax
    mov %ax, %ds
    mov %ax, %es
    mov %ax, %fs
    mov %ax, %gs

    pushl %esp
    call irq_handler
    add $0x4, %esp

    popl %eax
    mov %ax, %ds
    mov %ax, %es
    mov %ax, %fs
    mov %ax, %gs

    popa
    add $0x8, %esp
    sti
    iret

# This macro create a symbol, push the number of the interrupt on the stack
# and jump to the exception_handler
.macro isr_stub num
    .global isr\num
    isr\num:
        pushl $\num
        jmp isr_common
.endm

.macro irq_stub num isr_nb
    .global irq\num
    irq\num:
        cli
        pushl $\num
        pushl $\isr_nb
        jmp irq_common
.endm

isr_stub 0
isr_stub 1
isr_stub 2
isr_stub 3
isr_stub 4
isr_stub 5
isr_stub 6
isr_stub 7
isr_stub 8
isr_stub 9
isr_stub 10
isr_stub 11
isr_stub 12
isr_stub 13
isr_stub 14
isr_stub 15
isr_stub 16
isr_stub 17
isr_stub 18
isr_stub 19
isr_stub 20
isr_stub 21
isr_stub 22
isr_stub 23
isr_stub 24
isr_stub 25
isr_stub 26
isr_stub 27
isr_stub 28
isr_stub 29
isr_stub 30
isr_stub 31
irq_stub 0, 32
irq_stub 1, 33
irq_stub 2, 34
irq_stub 3, 35
irq_stub 4, 36
irq_stub 5, 37
irq_stub 6, 38
irq_stub 7, 39
irq_stub 8, 40
irq_stub 9, 41
irq_stub 10, 42
irq_stub 11, 43
irq_stub 12, 44
irq_stub 13, 45
irq_stub 14, 46
irq_stub 15, 47
