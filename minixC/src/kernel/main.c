#include <drivers/tty.h>

void kernel_main(void)
{
    struct tty tty;

    init_tty(&tty);
    launch_tty(&tty);
    for (;;);
}
