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

/**
 * You should not be here. If you are, it means something went wrong when loading the kernel.
 */
loadingError:
    jmp hang

# Infinite loop to avoid the kernel to crash
hang:
    jmp hang
