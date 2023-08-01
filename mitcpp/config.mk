##
## This is the configuration file for the MIT C++ version of Jackos
## It holds all the configuration variables of the MIT C++ version of Jackos
##

## Global variables
OS_NAME 			:= MITJackos

## Echo COLORS
GREEN 				:= \033[0;32m
RED 				:= \033[0;31m
NC 					:= \033[0m

## Project folders
SRC_DIR				:= $(PROJECT_PWD)/src
BOOT_NAME			:= boot
BOOT_DIR			:= $(SRC_DIR)/$(BOOT_NAME)
OBJ_DIR				:= $(PROJECT_PWD)/obj
BIN_FOLDER			:= $(PROJECT_PWD)/bin
KERNEL_FOLDER		:= $(SRC_DIR)/kernel
GENERATED_FOLDERS	:= $(OBJ_DIR) \
					$(BIN_FOLDER) \

## Project Binaries
KERNEL_IMG			:= $(BIN_FOLDER)/$(OS_NAME).img
BOOT_BIN_NAME		:= $(BOOT_NAME).bin
BOOT_BIN			:= $(OBJ_DIR)/$(BOOT_NAME)/$(BOOT_BIN_NAME)
KERNEL_LINKER		:= $(KERNEL_FOLDER)/kernel.ld

## Project Submodules to build
## PROJECT_PWD is set in the main Makefile
SUBMODULES			:= $(PROJECT_PWD)/$(BOOT_DIR)

## Binaries
CC					:= $(HOME)/cc/bin/i686-elf-g++
AS					:= $(HOME)/cc/bin/i686-elf-as
QEMU				:= qemu-system-i386
LD					:= $(HOME)/cc/bin/i686-elf-ld
PYTHON				:= python3
OBJCOPY				:= $(HOME)/cc/bin/i686-elf-objcopy

## Flags
CFLAGS				:= -W -Wall -Wextra -Werror
ASFLAGS				:=
QEMU_FLAGS			:= -serial mon:stdio
LD_FLAGS			:=
