#include <stdbool.h>
#include "kernel/Kernel.hpp"
#include "Types.hpp"

void Kernel::run()
{
	this->vga.puts("Hello World");

	HeapString str("Stored in heap!");

	this->vga.puts("\nGDT Initialization...");
	this->gdt.init();
	this->vga.puts("\nIDT Initialization...");
	this->idt.init();
	this->vga.puts("\nKeyboard Initialization...");
	this->keyboard.init(&this->idt);

	this->vga.puts("\nEverything PASSED\n");
	this->vga.puts(str.c_str());
}
