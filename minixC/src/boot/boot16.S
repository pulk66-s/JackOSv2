#
# This file contains the boot process of the system, it's the first code being
# Executed by the CPU.
#
# @author: pulk66-s
# last modified: 2023.09.20 
#

# This is the first label executed, it's the entry point of the system.
# Actually we are in the real mode, so we need to use the 16 bit code.
.globl _start
_start:
    .code16 # This is the directive to use the 16 bit code.
    cli     # We need to clear all the existing interrupts, the BIOS may have
            # some interrupts enabled.
    cld     # We need to clear the direction flag, it may be set by the BIOS.
            # So we need to clear it before we start to use the string

    # Cleaning the registers
    xorw %ax, %ax
    movw %ax,%ds
    movw %ax,%es
    movw %ax,%ss

    mov $0x53, %al
    call _print_char

    call enable_a20
    jc _enable_fails

    call check_a20
    cmp $1, %ax
    jne _enable_fails

    jmp switch_to_32

_enable_succeed:
    mov $0x59, %al
    call _print_char
    jmp inf_loop

_enable_fails:
    mov $0x4E, %al
    call _print_char
    jmp inf_loop

inf_loop:
    jmp inf_loop

.include "boot/switch32.S"
.include "boot/a20.S"
.include "boot/print.S"

_print_char:
    movb $0x0e, %ah
    movb $0x00, %bh
    int $0x10
    ret
