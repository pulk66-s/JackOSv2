##
## Makefile configuration file
## It contains everything that can be modified by the user
##
## @author: pulk66-s
## last update: 2023.09.20
##

# Must not be changed by the user
RELATIVE_ROOT_PATH	?=	.

# The name of the project
PROJECT_NAME		:= 	MJackOS

# The path of all generated binaries
BIN_DIR				:=	$(RELATIVE_ROOT_PATH)/bin

# The name of the output file
OUTPUT_NAME 		:= 	$(PROJECT_NAME)
KERNEL_IMG			:= 	${BIN_DIR}/$(OUTPUT_NAME).img

#########################
## Makefile log colors ##
#########################

NC		:=	\033[0m
RED		:=	\033[0;31m
GREEN	:=	\033[0;32m
YELLOW	:=	\033[0;33m

#######################
## Compiler binaries ##
#######################

BIN_FOLDER	:=	~/cc/bin
AS			:=	${BIN_FOLDER}/i686-elf-as
CC			:=	${BIN_FOLDER}/i686-elf-gcc
LD			:=	${BIN_FOLDER}/i686-elf-ld
OBJDUMP		:=	${BIN_FOLDER}/i686-elf-objdump
OBJCOPY		:=	${BIN_FOLDER}/i686-elf-objcopy
QEMU		:=	qemu-system-i386
PYTHON		:=	python3

# Flags
ASFLAGS		:=
CFLAGS		:=
LDFLAGS		:=	-m elf_i386
QEMU_FLAGS	:=	-serial mon:stdio
