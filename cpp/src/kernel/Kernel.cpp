#include <stdbool.h>
#include <kernel/Kernel.hpp>
#include "Types.hpp"

namespace JO::Kernel {
	static Kernel *kernel = new Kernel();

	void Kernel::run()
	{
		this->vga.puts("Hello World");

		JO::Libs::Types::String::HeapString str("Stored in heap!");

		this->vga.puts("\nGDT Initialization...");
		this->gdt.init();
		this->vga.puts("\nIDT Initialization...");
		this->idt.init();
		this->vga.puts("\nKeyboard Initialization...");
		this->keyboard.init(&this->idt);

		this->vga.puts("\nEverything PASSED\n");
		this->vga.puts(str.c_str());
	}

	Kernel *Kernel::getKernel()
	{
		return kernel;
	}

	struct Kernel::Context Kernel::getContext()
	{
		return (struct Kernel::Context) {
			.vga = &this->vga,
			.idt = &this->idt,
			.gdt = &this->gdt,
			.keyboard = &this->keyboard
		};
	}
}