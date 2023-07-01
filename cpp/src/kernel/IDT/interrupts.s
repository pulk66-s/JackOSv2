.extern isr_handler
.extern irq_handler

isr_common_stub:
    pushal

    xorl %eax, %eax
    movw %ds, %ax
    push %eax                # save the data segment descriptor
    
    movw $0x10, %ax          # kernel data segment descriptor
    movw %ax, %ds
    movw %ax, %es
    movw %ax, %fs
    movw %ax, %gs
    
    push %esp                # push esp --> C function parameter
    call isr_handler
    add $4, %esp

    pop %eax
    movw %ax, %ds
    movw %ax, %es
    movw %ax, %fs
    movw %ax, %gs

    popal
    add $8, %esp              # Cleans up the pushed error code and pushed ISR number
    sti
    iret
.endm

.global irq_common_stub
irq_common_stub:
    pushal

    xorl %eax, %eax
    movw %ds, %ax
    push %eax                # save the data segment descriptor
    
    movw $0x10, %ax          # kernel data segment descriptor
    movw %ax, %ds
    movw %ax, %es
    movw %ax, %fs
    movw %ax, %gs
    
    push %esp                # push esp --> C function parameter
    call irq_handler
    add $4, %esp

    pop %eax
    movw %ax, %ds
    movw %ax, %es
    movw %ax, %fs
    movw %ax, %gs

    popal
    add $8, %esp              # Cleans up the pushed error code and pushed ISR number
    sti
    iret
.endm


.text

# 0: Divide By Zero Exception
.global isr0
isr0:
    cli
    push $0
    push $0
    jmp isr_common_stub
# 1: Debug Exception
.global isr1
isr1:
    cli
    push $0
    push $1
    jmp isr_common_stub
# 2: Non Maskable Interrupt Exception
.global isr2
isr2:
    cli
    push $0
    push $2
    jmp isr_common_stub
# 3: Int 3 Exception
.global isr3
isr3:
    cli
    push $0
    push $3
    jmp isr_common_stub
# 4: INTO Exception
.global isr4
isr4:
    cli
    push $0
    push $4
    jmp isr_common_stub
# 5: Out of Bounds Exception
.global isr5
isr5:
    cli
    push $0
    push $5
    jmp isr_common_stub
# 6: Invalid Opcode Exception
.global isr6
isr6:
    cli
    push $0
    push $6
    jmp isr_common_stub
# 7: Coprocessor Not Available Exception
.global isr7
isr7:
    cli
    push $0
    push $7
    jmp isr_common_stub
# 8: Double Fault Exception (With Error Code!)
.global isr8
isr8:
    cli
    push $8
    jmp isr_common_stub
# 9: Coprocessor Segment Overrun Exception
.global isr9
isr9:
    cli
    push $0
    push $9
    jmp isr_common_stub
# 10: Bad TSS Exception (With Error Code!)
.global isr10
isr10:
    cli
    push $10
    jmp isr_common_stub
# 11: Segment Not Present Exception (With Error Code!)
.global isr11
isr11:
    cli
    push $11
    jmp isr_common_stub
# 12: Stack Fault Exception (With Error Code!)
.global isr12
isr12:
    cli
    push $12
    jmp isr_common_stub
# 13: General Protection Fault Exception (With Error Code!)
.global isr13
isr13:
    cli
    push $13
    jmp isr_common_stub
# 14: Page Fault Exception (With Error Code!)
.global isr14
isr14:
    cli
    push $14
    jmp isr_common_stub
# 15: Reserved Exception
.global isr15
isr15:
    cli
    push $0
    push $15
    jmp isr_common_stub
# 16: Floating Point Exception
.global isr16
isr16:
    cli
    push $0
    push $16
    jmp isr_common_stub
# 17: Alignment Check Exception
.global isr17
isr17:
    cli
    push $17
    jmp isr_common_stub
# 18: Machine Check Exception
.global isr18
isr18:
    cli
    push $18
    jmp isr_common_stub

# Reserved or unused
.global isr19
isr19:
    cli
    push $0
    push $19
    jmp isr_common_stub
.global isr20
isr20:
    cli
    push $0
    push $20
    jmp isr_common_stub
.global isr21
isr21:
    cli
    push $21
    jmp isr_common_stub
.global isr22
isr22:
    cli
    push $0
    push $22
    jmp isr_common_stub
.global isr23
isr23:
    cli
    push $0
    push $23
    jmp isr_common_stub
.global isr24
isr24:
    cli
    push $0
    push $24
    jmp isr_common_stub
.global isr25
isr25:
    cli
    push $0
    push $25
    jmp isr_common_stub
.global isr26
isr26:
    cli
    push $0
    push $26
    jmp isr_common_stub
.global isr27
isr27:
    cli
    push $0
    push $27
    jmp isr_common_stub
.global isr28
isr28:
    cli
    push $0
    push $28
    jmp isr_common_stub
.global isr29
isr29:
    cli
    push $0
    push $29
    jmp isr_common_stub
.global isr30
isr30:
    cli
    push $0
    push $30
    jmp isr_common_stub
.global isr31
isr31:
    cli
    push $0
    push $31
    jmp isr_common_stub

# IRQs
.global irq0
irq0:
    cli
    push $0
    push $32
    jmp irq_common_stub
.global irq1
irq1:
    cli
    push $1
    push $33
    jmp irq_common_stub
.global irq2
irq2:
    cli
    push $2
    push $34
    jmp irq_common_stub
.global irq3
irq3:
    cli
    push $3
    push $35
    jmp irq_common_stub
.global irq4
irq4:
    cli
    push $4
    push $36
    jmp irq_common_stub
.global irq5
irq5:
    cli
    push $5
    push $37
    jmp irq_common_stub
.global irq6
irq6:
    cli
    push $6
    push $38
    jmp irq_common_stub
.global irq7
irq7:
    cli
    push $7
    push $39
    jmp irq_common_stub
.global irq8
irq8:
    cli
    push $8
    push $40
    jmp irq_common_stub
.global irq9
irq9:
    cli
    push $9
    push $41
    jmp irq_common_stub
.global irq10
irq10:
    cli
    push $10
    push $42
    jmp irq_common_stub
.global irq11
irq11:
    cli
    push $11
    push $43
    jmp irq_common_stub
.global irq12
irq12:
    cli
    push $12
    push $44
    jmp irq_common_stub
.global irq13
irq13:
    cli
    push $13
    push $45
    jmp irq_common_stub
.global irq14
irq14:
    cli
    push $14
    push $46
    jmp irq_common_stub
.global irq15
irq15:
    cli
    push $15
    push $47
    jmp irq_common_stub
