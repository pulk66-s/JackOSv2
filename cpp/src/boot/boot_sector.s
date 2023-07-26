# Code 16-bit, the boot sector start from 0x7C00 in 16-bit mode
.code16

.global _start

_start:
	# Starting message
	mov	$msg, %si
	call print_msg
	mov $newline, %si
	call print_msg

	# Remember that the BIOS sets up the boot drive in 'dl' on boot
	mov %dl, BOOT_DRIVE
	
	# Setup the stack memory. It's described by two differents registers
	# bp: Base Pointer
	# sp: Stack Pointer
	# We set the base stack memory at 0x9000
	mov $0x9000, %bp
	mov %bp, %sp

	call load_kernel

	mov $error, %si
	call print_msg
	call switch_to_pm

# Load the kernel from the disk
.code16
load_kernel:
	mov $load_kernel_msg, %si
	call print_msg

	mov $KERNEL_OFFSET, %bx
	mov $0x02, %ah
	mov BOOT_DRIVE, %dl
	call disk_load
	ret

.code32
BEGIN_PM:
	call KERNEL_OFFSET
	jmp hang

hang:
	jmp hang

.code16

BOOT_DRIVE: .byte 0x00

# The kernel is loaded at 0x1000
KERNEL_OFFSET = 0x1000

.include "print.s"
.include "message.s"
.include "switch.s"
.include "disk.s"

# We need to fill the rest of the 510 bytes with 0x00
# So we use the .fill directive
.org 510

# Boot signature, It's a must or BIOS won't boot the code
.word 0xaa55

