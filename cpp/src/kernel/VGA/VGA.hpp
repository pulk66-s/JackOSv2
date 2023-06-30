#ifndef __JACKOS_KERNEL_VGA_VGA_HPP__
    #define __JACKOS_KERNEL_VGA_VGA_HPP__

    #include <stdint.h>
    #include <stddef.h>

    #include "Types/HeapString.hpp"

/**
 * @brief      VGA constants
 * The VGA is a 80x25 character display starting at 0xB8000.
 * Each character is 2 bytes long.
 * - The first byte is the ASCII character.
 * - The second byte is the color.
 * So it's a 80x25x2 bytes buffer.
*/
    #define VGA_WIDTH   80
    #define VGA_HEIGHT  25
    #define VGA_BUFFER  0xB8000

/**
 * @brief      VGA types
 * Types to make the code more readable.
*/
typedef uint8_t     VGA_entry_color;
typedef uint16_t    VGA_entry;
typedef VGA_entry*  VGA_buffer;

/**
 * @brief      VGA class
 * It's a class that handles the VGA buffer.
 * It works like a terminal, with colors and different printing functions.
*/
class VGA
{

public:
    /**
     * @brief      VGA colors
     * List of all the colors available for the VGA.
     * The first 8 colors are the normal ones, the last 8 are the bright ones.
     * See the official VGA documentation for more information.
     * https://en.wikipedia.org/wiki/VGA-compatible_text_mode#Color_attributes
    */
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

    /**
     * @brief      Put a character on the VGA buffer
     * It print a char on the next available position.
    */
    void putc(unsigned char c);

    /**
     * @brief      Put a const char * on the VGA buffer
     * It print a string on the next available position.
    */
    void puts(const char *str);

    /**
     * @brief      Put a AString on the VGA buffer
     * It print a string on the next available position.
    */
    // void puts(AString str);

private:
    size_t row;
    size_t col;
    VGA_entry_color color;
    VGA_buffer buffer;

    inline VGA_entry_color colorEntry(enum VGA::color fg, enum VGA::color bg);
    inline VGA_entry vgaEntry(unsigned char c, VGA_entry_color color);
};

#endif