#
# File to print char and ascii value on the screen with BIOS
#

# Print char and ascii value on the screen
# Parameters:
#   stack-4: char to print
.global print_char_16
print_char_16:
    .code16
    push %bp
    mov %sp, %bp
    mov 4(%bp), %al
    mov $0x0e, %ah
    int $0x10
    pop %bp
    ret
