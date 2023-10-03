#ifndef __JOS_INC_DRIVERS_TTY_DATA_H__
#define __JOS_INC_DRIVERS_TTY_DATA_H__

#include <lib/types.h>
#include <drivers/vga.h>

#define TTY_MAX_PROMPT_SIZE 8       // Max size of the prompt
#define TTY_MAX_LINE_SIZE   128     // Max size of a line
#define TTY_MAX_COL_SIZE    20      // Max size of a column

// Max size of the buffer
#define TTY_MAX_BUFF_SIZE   TTY_MAX_LINE_SIZE * TTY_MAX_COL_SIZE

/**
 * @brief   Thoses typedefs are used to define the tty driver interface.
*/
typedef void (*display_char)(uint8_t, uint8_t, uint8_t, char);
typedef void (*display_string)(uint8_t, uint8_t, uint8_t, const char *);
typedef void (*display_int)(uint8_t, uint8_t, uint8_t, int);
typedef void (*get_char)(uint8_t, uint8_t);
typedef void (*clear)(void);

struct tty_print_interface {
    display_char display_char;
    display_string display_string;
    display_int display_int;
    get_char get_char;
    clear clear;
};

struct tty {
    struct tty_print_interface display;
    size_t x, y;
    uint8_t color;
    char prompt[TTY_MAX_PROMPT_SIZE];
    char buff[TTY_MAX_BUFF_SIZE];
};

#endif
