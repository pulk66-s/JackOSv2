#include <mmu.hpp>

/**
 * 
 * This file is the boot processus of the kernel of the MIT JackOS project.
 * It's written in GNU Assembly, it switch from 16 bits (real mode) to 32 bits (protected mode).
 * It disable the A20 line, load the gdt and load the kernel from the disk.
 * This code is executting after the BIOS, and the BIOS doesn't clean it's data
 * 
 */

.code16
.globl start
start:
    # The bios can setup its own interrupts, we need to disable them to avoid conflicts
    cli
    # The bios can manipulate strings, we need to reset all the strings registers
    cld

    # The bios use and doesn't clean its segment registers, we need to clean them
    xorw %ax, %ax       # SEGMENT 0
    movw %ax, %ds       # DS    ->  Data Segment
    movw %ax, %es       # ES    ->  Extra Segment
    movw %ax, %ss       # SS    ->  Stack Segment

/**
 * Enable A20:
 * For backwards compatibility with the earliest PCs, physical
 * address line 20 is tied low, so that addresses higher than
 * 1MB wrap around to zero by default.  This code undoes this
 * You must follow a procedure to enable A20:
 * 1. Wait until the input 0x64 is clear (inb)
 * 2. Send 0xd1 to 0x64 (outb)
 * 3. Wait until the input 0x64 is clear (inb)
 * 4. Send 0xdf to 0x60 (outb)
 */
enableA20_step1:
    inb $0x64, %al
    testb $0x2, %al     # Test if the bit 1 is set
    jnz enableA20_step1 # If it's set, it means the input is not clear, we need to wait

    movb $0xd1, %al
    outb %al, $0x64

enableA20_step2:
    inb $0x64, %al
    testb $0x2, %al     # Test if the bit 1 is set
    jnz enableA20_step2 # If it's set, it means the input is no²t clear, we need to wait

    movb $0xdf, %al
    outb %al, $0x60

.set PROT_MODE_CSEG, 0x8         # kernel code segment selector
.set PROT_MODE_DSEG, 0x10        # kernel data segment selector

/**
 * This label load the GDT and switch to protected mode
 * Since we are in 16 bits, we can't use the 32 bits instructions and their features
 * So we need to pass from 16 bits to 32 bits
 */
switch_from_16_to_32:
    lgdt gdt_descriptor

    # We need to set the first bit of the cr0 register to 1 to enable protected mode
    movl %cr0, %eax
    orl $0x1, %eax
    movl %eax, %cr0

    # Jump to next instruction, but in 32-bit code segment.
    # Switches processor into 32-bit mode.
    ljmp $PROT_MODE_CSEG, $protected_code_seg

/**
 * This is the first label when we are in 32 bits
 * We need to set the data segment to 0x10 to avoid conflicts.
 * Every datas will be loaded at the adress 0x10 (DATA SEGMENT) to avoid overwriting the code
 */
.code32
protected_code_seg:
    movw $PROT_MODE_DSEG, %ax

    movw %ax, %ds                # -> DS: Data Segment
    movw %ax, %es                # -> ES: Extra Segment
    movw %ax, %fs                # -> FS
    movw %ax, %gs                # -> GS
    movw %ax, %ss                # -> SS: Stack Segment

    # Set up the stack pointer and call into C.
    movl $start, %esp
    call bootmain

/**
 * You should not be here. If you are, it means something went wrong when loading the kernel.
 */
loadingError:
    jmp hang

# Infinite loop to avoid the kernel to crash
hang:
    jmp hang

/**
 * This is the GDT Description
 */
.p2align 2  # force 4 byte alignment
gdt:
    SEG_NULL
    SEG(SEG_EXECUTABLE | SEG_READABLE, 0x0, 0xffffffff) # code seg
    SEG(SEG_WRITABLE, 0x0, 0xffffffff)                  # data seg
gdt_end:

/**
 * This is the GDT Descriptor
 * It describe the adress and the size of the GDT
 */
gdt_descriptor:
    .word gdt_end - gdt - 1     # Size of the GDT
    .long gdt                   # Adress of the GDT
