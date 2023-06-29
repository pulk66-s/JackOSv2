#ifndef __JACKOS_KERNEL_VGA_VGA_HPP__
    #define __JACKOS_KERNEL_VGA_VGA_HPP__

    #include <stdint.h>
    #include <stddef.h>

    #define VGA_WIDTH   80
    #define VGA_HEIGHT  25
    #define VGA_BUFFER  0xB8000

typedef uint8_t VGA_entry_color;
typedef uint16_t VGA_entry;
typedef VGA_entry *VGA_buffer;

class VGA
{

public:
    enum color
    {
        BLACK = 0,
        BLUE = 1,
        GREEN = 2,
        CYAN = 3,
        RED = 4,
        MAGENTA = 5,
        BROWN = 6,
        LIGHT_GREY = 7,
        DARK_GREY = 8,
        LIGHT_BLUE = 9,
        LIGHT_GREEN = 10,
        LIGHT_CYAN = 11,
        LIGHT_RED = 12,
        LIGHT_MAGENTA = 13,
        LIGHT_BROWN = 14,
        WHITE = 15,
    };

    VGA(void);

    void putc(unsigned char c);

private:
    size_t row;
    size_t col;
    VGA_entry_color color;
    VGA_buffer buffer;

    void init(void);
    VGA_entry_color colorEntry(enum VGA::color fg, enum VGA::color bg);
    VGA_entry vgaEntry(unsigned char c, VGA_entry_color color);
};

#endif