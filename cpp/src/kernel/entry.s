.code32
entry_point:
    call KERNEL_OFFSET

# Infinite loop for the bootloader
# It needs to be infinite, because the BIOS will keep calling the bootloader
hang:
	jmp	hang

KERNEL_OFFSET = 0x1000
