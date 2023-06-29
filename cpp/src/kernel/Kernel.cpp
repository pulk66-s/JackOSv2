#include <stdbool.h>
#include "kernel/Kernel.hpp"

void Kernel::run()
{
	this->vga.putc('H');
}
