/**
 * @file main.cpp
 * @brief The main function of the boot system.
 * @details
 * This file contains the main function of the boot system. It start with C code
 * and then call the C++ code.
*/

// Mandatory to setup jump from the assembly code to the C code
extern "C" {
    /**
     * @brief The main function of the boot system.
    */
    void bootmain(void) {
        for (;;);
    }
}