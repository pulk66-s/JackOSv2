# Code 16-bit, the boot sector start from 0x7C00 in 16-bit mode
.code16

.global _start

_start:
	# We need to clean the interrupt flag, because we are going to use the interrupt
	cli
	
	xor	%ax, %ax
	mov	%ax, %ds
	mov	$msg, %si
	cld

loop:
	# Load the byte at SI (the next character of the message) into AL
	lodsb

	# Check if the character is null (end of the string)
	or	%al, %al
	jz	hang	# If null, jump to the hang label to create an infinite loop

	# If the character is not null, prepare and invoke the BIOS interrupt to print the character
	mov	$0x0E, %ah	# Function number 0x0E - Write Character Teletype
	mov	$0x00, %bh	# Page number (0x00 for video page)
	int	$0x10		# Invoke BIOS interrupt 0x10

	# Continue with the next character in the message
	jmp	loop

hang:
	jmp	hang

# Message to print on the screen
msg:
	.string "BOOTLOADER"

# We need to fill the rest of the 510 bytes with 0x00
# So we use the .fill directive
.org 510

# Boot signature, It's a must or BIOS won't boot the code
.word 0xaa55

