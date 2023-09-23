#
# This file contains the enabler for the A20 line
#
# @author: pulk66-s
# last modified: 2023.09.20
#

# Purpose: to enable the A20 line
# Returns: cf - set on error
.global enable_a20
enable_a20:
    clc         # Clear the carry flag
    pusha       # Save all registers
    mov $0, %bh # bh = 0

    call check_a20
    jc .fast_gate

    test %ax, %ax
    jnz _enable_a20_done

    call _bios_function_gate_support
    mov %al, %bl                # bl = al
    test $1, %bl                # Test if bit 0 is set
    jnz _keyboard_controller    # If bit 0 is set, jump to _keyboard_controller

    test $2, %bl                # Test if bit 1 is set
    jnz .fast_gate              # If bit 1 is set, jump to .fast_gate

_bios_int:
    mov $0x2401, %ax            # ax = 0x2401
    int $0x15                   # INT 0x15 with ax = 0x2401
    jc _enable_a20_fail         # If the carry flag is set, jump to _enable_a20_fail

    test %ah, %ah               # Test if ah == 0
    jnz _enable_a20_fail        # If ah != 0, jump to _enable_a20_fail

    call check_a20              # Check if the A20 line is enabled
    test %ax, %ax               # Test if the A20 line is enabled
    jnz _enable_a20_done        # If the A20 line is enabled, jump to _enable_a20_done

.fast_gate:
    in $0x92, %al               # Read the system control port (0x92)
    test $2, %al                # Test if bit 1 is set
    jnz _enable_a20_done        # If bit 1 is set, jump to _enable_a20_done

    or $2, %al                  # Set bit 1
    and $0xfe, %al              # Clear bit 0, 0xfe = 0b11111110
    out %al, $0x92              # Write the system control port (0x92)

    call check_a20              # Check if the A20 line is enabled
    test %ax, %ax               # Test if the A20 line is enabled, test %ax, %ax is equivalent to cmp $0, %ax
    jnz _enable_a20_done        # If the A20 line is enabled, jump to _enable_a20_done

    test %bh, %bh               # Test if bh == 0
    jnz _enable_a20_fail        # If bh != 0, jump to _enable_a20_fail

    jmp _keyboard_controller    # Enable the A20 line with the keyboard controller

_enable_a20_fail:
    stc

_enable_a20_done:
    popa
    ret

#
#
# Other functions to check / activate the A20 line
#
#

# Purpose: try to enable the A20 line with the BIOS function gate INT 0x15
# Returns: cf - set on error
_bios_function_gate_support:
    push %bx
    clc

    mov $0x2403, %ax
    int $0x15
    jc _bios_function_gate_fail

    test %ah, %ah   # test %ah, %ah is equivalent to cmp $0, %ah
    jnz _bios_function_gate_fail

    mov %bx, %ax
    pop %bx
    ret

_bios_function_gate_fail:
    stc
    pop %bx
    ret

#
#
# Keyboard controller source code for A20
#
#

_keyboard_controller:
    call _enable_a20_keyboard_controller    # Enable the A20 line with the keyboard controller
    call check_a20                          # Check if the A20 line is enabled
    test %ax, %ax                           # Test if the A20 line is enabled
    jnz _enable_a20_done                    # If the A20 line is enabled, jump to _enable_a20_done

    mov $1, %bh                             # bh = 1

    test $2, %bl                            # Test if bit 1 is set
    jnz .fast_gate                          # If bit 1 is set, jump to .fast_gate
    jmp _enable_a20_fail                    # Else Jump to _enable_a20_fail

_enable_a20_keyboard_controller:
    cli             # Clearing all interrupts

    call _wait_io1  # Waiting until the input buffer is empty
    mov $0xad, %al
    out %al, $0x64

    call _wait_io1  # Waiting until the input buffer is empty
    mov $0xd0, %al
    out %al, $0x64

    call _wait_io2  # Waiting until the output buffer is full
    in $0x60, %al
    push %eax

    call _wait_io1  # Waiting until the input buffer is empty
    mov $0xd1, %al
    out %al, $0x64

    call _wait_io1  # Waiting until the input buffer is empty
    pop %eax
    or $2, %al
    out %al, $0x60

    call _wait_io1  # Waiting until the input buffer is empty
    mov $0xae, %al
    out %al, $0x64

    call _wait_io1  # Waiting until the input buffer is empty
    sti             # Setting all interrupts
    ret

# Waiting until the input buffer is empty
_wait_io1:
    in $0x64, %al
    test $2, %al
    jnz _wait_io1
    ret

# Waiting until the output buffer is full
_wait_io2:
    in $0x64, %al
    test $1, %al
    jnz _wait_io1
    ret

# Purpose: to check the status of the a20 line in a completely self-contained state-preserving way.
#          The function can be modified as necessary by removing push's at the beginning and their
#          respective pop's at the end if complete self-containment is not required.
#
# Returns: 0 in ax if the a20 line is disabled (memory wraps around)
#          1 in ax if the a20 line is enabled (memory does not wrap around)
.global check_a20
check_a20:
    # save the state of the registers

    pushf
    push %ds
    push %es
    push %di
    push %si

    cli

    xor %ax, %ax            # ax = 0
    mov %ax, %ds            # ds = 0
    mov $0x0500, %si        # si = 0x0500

    not %ax                 # ax = 0xffff
    mov %ax, %es            # es = 0xffff
    mov $0x0510, %di        # di = 0x0510

    mov %ds:(%si), %al      # al = ds:si
    mov %al, .BufferBelowMB # .BufferBelowMB = al
    mov %es:(%di), %al      # al = es:di
    mov %al, .BufferOverMB  # .BufferOverMB = al

    mov $0x1, %ah           # ah = 1
    mov $0x0, %ds:(%si)     # ds:si = 0x0000
    mov $0x1, %es:(%di)     # es:di = 0x0001
    mov %ds:(%si), %al      # al = ds:si
    cmp %es:(%di), %al      # cmp al, es:di
    jne _check_a20_exit
    dec %ah

_check_a20_exit:
    mov .BufferBelowMB, %al # al = .BufferBelowMB
    mov %al, %ds:(%si)      # ds:si = al
    mov .BufferOverMB, %al  # al = .BufferOverMB
    mov %al, %es:(%di)      # es:di = al
    shr $0x8, %ax           # ax = ax >> 8
    sti
    pop %es
    pop %ds
    pop %di
    pop %si
    popf
    ret

    .BufferBelowMB: .byte 0
    .BufferOverMB:  .byte 0
