#include "kernel/Kernel.hpp"

// Check if the compiler thinks you are targeting the wrong operating system.
#if defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif

// This OS will only work for the 32-bit ix86 targets.
#if !defined(__i386__)
#error "This OS needs to be compiled with a ix86-elf compiler"
#endif

/**
 * @brief      The kernel entry point
 * Extern is used to tell the compiler that the function is defined elsewhere.
 * The kernel_main function is called by the assembly code.
*/
extern "C"
{
	void kernel_main(void)
	{
		Kernel *kernel = Kernel::getKernel();

		kernel->run();
		for (;;);
	}
}