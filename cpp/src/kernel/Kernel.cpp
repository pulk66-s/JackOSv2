#include <stdbool.h>
#include "kernel/Kernel.hpp"
#include "Types.hpp"

void Kernel::run()
{
	this->vga.puts("Hello World");

	HeapString str("Stored in heap!");

	this->gdt.init();
	this->idt.init();
	this->idt.enableEntry(33);
	this->vga.puts("PASSED");
	this->vga.puts(str.c_str());
}
