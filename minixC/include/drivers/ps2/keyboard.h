#ifndef __JOS_INCLUDE_DRIVERS_PS2_KEYBOARD_H__
#define __JOS_INCLUDE_DRIVERS_PS2_KEYBOARD_H__

#include <lib/types.h>

// Flag that define if the shift key is pressed or not
#define SHIFT_FLAG              1 << 7

// Maximum number of keys in the buffer
#define MAX_KEYS_BUFFER         20

// Keyboard layout size
#define KB_LAYOUT_SIZE          60

// The index of the keyboard interrupt in the IDT
#define PS2_KEYBOARD_IDT_IDX    0x21

// Get the scancode from the keyboard with this PIC port
#define PS2_KEYBOARD_DATA_PORT  0x60

/**
 * @brief   Initialize the PS/2 keyboard driver.
*/
void init_ps2_keyboard(void);

/**
 * @brief   Convert a scancode to a character.
*/
char keyboard_scancode_to_char(uint8_t scancode);

/**
 * @brief       Add a key to the linked list.
 * @param   c   The character to add.
*/
void keyboard_keys_list_add(char c);

/**
 * @brief       Get the first key in the linked list.
 * @return      The first key in the linked list.
*/
char keyboard_keys_list_get(void);

/**
 * @brief       Read and block until a key is pressed.
*/
char keyboard_read(void);

#endif
