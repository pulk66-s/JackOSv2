; This is GNU ASM boot sector code for i686 architecture
; This code is written by pulk66-s

__start:
    ; Infinite loop to handle all the OS process
    jmp __start

; We need to fill the rest of the 510 bytes with 0x00
; So we use the .fill directive
times 510-($-$$) db 0

; Boot signature, It's a must or BIOS won't boot the code
dw 0xAA55
