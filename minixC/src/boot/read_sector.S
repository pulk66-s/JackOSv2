#
# Read the sector to have all the bootcode in memory
#

read_sector_16:
    pusha

    mov $0x02, %ah      # Read function
    mov $0x01, %al      # Number of sectors to read
    mov $0x7E00, %bx    # Buffer address
    mov $0x0, %dh       # Head number
    mov $0x80, %dl      # Drive number
    mov $0x0, %ch       # Track number
    mov $0x2, %cl       # Sector number

    int $0x13
    jc .error

    mov $0x44, %al
    call _print_char
    popa
    ret

.error:
    mov $0x43, %al
    call _print_char
    popa
    ret
