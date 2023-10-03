#include <drivers/ps2/keyboard.h>

/**
 * @brief   Convert a scancode to a character with the azerty layout.
*/
static char azerty_layer(uint8_t scancode)
{
    char layer[] = {
        0,      // Error
        0,      // Escape
        '&', 'e', '"', '\'', '(', '-', 'e', '_', 'ç', 'a', ')', '=',
        '\b',   // backspace
        '\t',   // tab
        'a', 'z', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '^', '$',
        '\n',   // enter
        0,      // control key
        'q', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 'm', 'ù', '*',
        0,      // left shift
        '<', 'w', 'x', 'c', 'v', 'b', 'n', ',', ';', ':', '!', 0,
        0,      // right shift
        '*',    // keypad *
        0,      // left alt
        ' ',    // space
        0,      // caps lock
        0,      // F1
    };
    int is_upper = 0;
    char c = 0;

    if (scancode & SHIFT_FLAG) {
        is_upper = 1;
        scancode &= ~SHIFT_FLAG; // Remove the shift flag
    }
    c = layer[scancode % KB_LAYOUT_SIZE];
    if (is_upper && c >= 'a' && c <= 'z') {
        c -= 32;
    }
    return c;
}

/**
 * @brief   Convert a scancode to a character with the qwerty layout.
*/
static char qwerty_layer(uint8_t scancode)
{
    char layer[] = {
        0,      // Error
        0,      // Escape
        '&', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-',
        '\b',   // backspace
        '\t',   // tab
        'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '^', '$',
        '\n',   // enter
        0,      // control key
        'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 'm', '`', '*',
        0,      // left shift
        '<', 'z', 'x', 'c', 'v', 'b', 'n', ',', ';', ':', '!', 0,
        0,      // right shift
        '*',    // keypad *
        0,      // left alt
        ' ',    // space
        0,      // caps lock
        0,      // F1
    };
    int is_upper = 0;
    char c = 0;

    if (scancode & SHIFT_FLAG) {
        is_upper = 1;
        scancode &= ~SHIFT_FLAG; // Remove the shift flag
    }
    c = layer[scancode % KB_LAYOUT_SIZE];
    if (is_upper && c >= 'a' && c <= 'z') {
        c -= 32;
    }
    return c;
}

/**
 * @brief   Convert a scancode to a character.
*/
char keyboard_scancode_to_char(uint8_t scancode)
{
    return azerty_layer(scancode);
}
