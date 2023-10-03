#include <drivers/ps2/keyboard.h>
#include <drivers/vga.h>
#include <drivers/pic.h>
#include <interrupts.h>

/**
 * @brief   Callback for the interrupt.
*/
static void ps2_keyboard_callback(struct registers *regs)
{
    uint8_t scancode = pic_read(PS2_KEYBOARD_DATA_PORT);
    char c = keyboard_scancode_to_char(scancode);

    if (c != 0) {
        keyboard_keys_list_add(c);
    }
}

/**
 * @brief   Initialize the PS/2 keyboard driver.
*/
void init_ps2_keyboard(void)
{
    set_callback(PS2_KEYBOARD_IDT_IDX, ps2_keyboard_callback);
}

/**
 * @brief       Read and block until a key is pressed.
*/
char keyboard_read(void)
{
    char c = 0;

    while (c == 0) {
        c = keyboard_keys_list_get();
    }
    return c;
}
