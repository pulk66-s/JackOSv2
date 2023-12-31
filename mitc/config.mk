##
## This is the configuration file for the MIT C version of Jackos
## It holds all the configuration variables of the MIT C version of Jackos
##

## Global names
OS_NAME 			:=	MITJackos
BOOT_NAME			:=	boot
KERNEL_NAME			:=	kernel
CLIB_NAME			:=	libclib

## Echo COLORS
GREEN 				:=	\033[0;32m
RED 				:=	\033[0;31m
YELLOW 				:=	\033[0;33m
NC 					:=	\033[0m

## Project folders
SRC_DIR				:=	$(PROJECT_PWD)/src
BOOT_DIR			:=	$(SRC_DIR)/$(BOOT_NAME)
KERNEL_DIR			:=	$(SRC_DIR)/$(KERNEL_NAME)
INCLUDE_FOLDER		:=	$(SRC_DIR)/include
LIB_DIR				:=	$(SRC_DIR)/$(CLIB_NAME)
OBJ_DIR				:=	$(PROJECT_PWD)/obj
BIN_FOLDER			:=	$(PROJECT_PWD)/bin
GENERATED_FOLDERS	:=	$(OBJ_DIR) $(BIN_FOLDER)

## Project Binaries
KERNEL_IMG			:=	$(BIN_FOLDER)/$(OS_NAME).img
BOOT_BIN			:=	$(OBJ_DIR)/$(BOOT_NAME)/$(BOOT_NAME).bin
KERNEL_BIN			:=	$(OBJ_DIR)/$(KERNEL_NAME)/$(KERNEL_NAME).bin
KERNEL_LINKER		:=	$(KERNEL_DIR)/kernel.ld
LIB_OBJ_FOLDER		:=	$(OBJ_DIR)/$(CLIB_NAME)

## Project Submodules to build
## PROJECT_PWD is set in the main Makefile
SUBMODULES			:=	$(PROJECT_PWD)/$(BOOT_DIR)

## Binaries
CC					:=	$(HOME)/cc/bin/i686-elf-gcc
AS					:=	$(HOME)/cc/bin/i686-elf-as
QEMU				:=	qemu-system-x86_64
LD					:=	$(HOME)/cc/bin/i686-elf-ld
PYTHON				:=	python3
OBJCOPY				:=	$(HOME)/cc/bin/i686-elf-objcopy
OBJDUMP				:=	$(HOME)/cc/bin/i686-elf-objdump
NM					:=	$(HOME)/cc/bin/i686-elf-nm
AR					:=	ar

## Flags
CFLAGS				:=	-W -Wall -Wextra -nostdinc -O1 -fno-builtin -fno-stack-protector -I$(SRC_DIR)
ASFLAGS				:=
QEMU_FLAGS			:= 	-serial mon:stdio
LD_FLAGS			:=	-m elf_i386

