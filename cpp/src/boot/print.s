print_msg:
	# Clear the direction flag, because we are going to use the lodsb instruction
	cld
	.loop:
		# Load the byte at SI (the next character of the message) into AL
		lodsb

		# Check if the character is null (end of the string)
		or	%al, %al
		jz	.end	# If null, jump to the hang label to create an infinite loop

		# If the character is not null, prepare and invoke the BIOS interrupt to print the character
		mov	$0x0E, %ah	# Function number 0x0E - Write Character Teletype
		mov	$0x00, %bh	# Page number (0x00 for video page)
		int	$0x10		# Invoke BIOS interrupt 0x10

		# Continue with the next character in the message
		jmp	.loop

	.end:
		ret
