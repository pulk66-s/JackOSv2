#include <stdbool.h>
#include "kernel/Kernel.hpp"
#include "Types/String.hpp"

void Kernel::run()
{
	this->vga.putc('H');
	this->vga.putc('e');

	this->vga.puts("LOOP");

	this->vga.putc('p');
}
