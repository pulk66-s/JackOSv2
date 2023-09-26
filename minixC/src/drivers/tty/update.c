#include <drivers/tty.h>
#include <drivers/vga.h>

/**
 * @brief           Init the tty
 * @param   tty     The tty to init
*/
void init_tty(struct tty *tty)
{
    init_vga(&tty->vga);
}

/**
 * @brief           Launch the tty
 * @param   tty     The tty to launch
*/
void launch_tty(struct tty *tty)
{
    char prompt[] = "JOS> ";

    vga_clear(&tty->vga);
    vga_println(&tty->vga, prompt);
    for (;;) {
        
    }
}
