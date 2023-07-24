##
## File configuration for Makefile
## It contains everything that you needs in your Makefile
##

## Texts Colors
## Usage: $(RED)Hello$(NC)
RED=\033[0;31m
GREEN=\033[0;32m
YELLOW=\033[0;33m
NC=\033[0m

## Compiler
CC=$(HOME)/cc/bin/i686-elf-g++
AS=$(HOME)/cc/bin/i686-elf-as
LD=$(HOME)/cc/bin/i686-elf-ld
NASM=nasm

LD_FLAGS=-Ttext 0x7c00
AS_FLAGS=
NASM_BOOT_FLAGS=-f bin
CC_FLAGS=

## Running software
QEMU=qemu-system-i386
QEMU_FLAGS=

## Files
BOOT_BIN_NAME=boot.bin
BOOT_ELF_NAME=boot.elf