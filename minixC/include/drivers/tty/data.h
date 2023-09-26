#ifndef __JOS_INC_DRIVERS_TTY_DATA_H__
#define __JOS_INC_DRIVERS_TTY_DATA_H__

#include <lib/types.h>
#include <drivers/vga.h>

struct tty {
    struct vga vga;
};

#endif
