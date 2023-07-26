.code16
# switch to protected mode
switch_to_pm:
    cli                            # 1. disable interrupts
    lgdt gdt_descriptor            # 2. load the GDT descriptor
    movl %cr0, %eax                # 3. move cr0 into eax
    orl $0x1, %eax                 #    set 32-bit mode bit in cr0
    movl %eax, %cr0

    jmp $0x08, $init_pm            # 4. far jump by using a different segment

.code32
# 32-bit mode code
init_pm:
    movw $DATA_SEG, %ax            # 5. update the segment registers
    movw %ax, %ds
    movw %ax, %ss
    movw %ax, %es
    movw %ax, %fs
    movw %ax, %gs

    movl $0x90000, %ebp            # 6. update the stack right at the top of the free space
    movl %ebp, %esp

    call BEGIN_PM                  # 7. Call a well-known label with useful code

.include "gdt.s"
