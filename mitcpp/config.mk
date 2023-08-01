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
GENERATED_FOLDERS	:= $(OBJ_DIR)	# It's generated from the $(PROJECT_PWD) folder

## Project Submodules to build
## PROJECT_PWD is set in the main Makefile
SUBMODULES			:= $(PROJECT_PWD)/$(BOOT_DIR)

## Binaries
CC					:= $(HOME)/cc/bin/i686-elf-g++
AS					:= $(HOME)/cc/bin/i686-elf-as
QEMU				:= qemu-system-i386

## Flags
CFLAGS				:= -W -Wall -Wextra -Werror
ASFLAGS				:=
QEMU_FLAGS			:=