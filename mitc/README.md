# MIT C Jackos

## Introduction

This project is a C version of Jackos but created with the MIT 6.828 course

## Documentation

See [./doc/README.md](./doc/README.md)

## Installation

This project is built in `C` and `GAS`. It's compiling using `make`, so be sure to download it.

If you are on a system using ELF architecture you can use the standard compiler `gcc` and `as` otherwise you must use the cross compiler `i386-elf-gcc` and `i386-elf-as`. (See [here](https://wiki.osdev.org/GCC_Cross-Compiler) for more information). I am using the cross compiler. If you are not you will need to change the `CC` and `AS` variables in the `Makefile` to `gcc` and `as` respectively and changes the `CFLAGS` and `ASFLAGS` variables by I don't know what.

## How to use

### Build

To build the project, simply run `make` in the root directory of the project.

### Run

To run the project with qemu, simply run `make qemu` in the root directory of the project after building it.


### Other

- To clean the project, simply run `make clean` in the root directory of the project.
- To full clean the project (with binaries), simply run `make fclean` in the root directory of the project.
- To rebuild the project, simply run `make re` in the root directory of the project.
