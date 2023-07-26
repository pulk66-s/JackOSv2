##
## This is the configuration file for the MIT C++ version of Jackos
## It holds all the configuration variables of the MIT C++ version of Jackos
##

## Global variables
OS_NAME 	:= MITJackos

## Echo COLORS
GREEN 		:= \033[0;32m
RED 		:= \033[0;31m
NC 			:= \033[0m

## Project folders
SRC_DIR		:= src
BOOT_DIR	:= $(SRC_DIR)/boot

## Project Submodules to build
## PROJECT_PWD is set in the 
SUBMODULES	:= $(PROJECT_PWD)/$(BOOT_DIR)

## Compilers
CC			:= $(HOME)/cc/bin/i686-elf-g++
AS			:= $(HOME)/cc/bin/i686-elf-as

## Flags
CFLAGS		:= -W -Wall -Wextra -Werror
ASFLAGS		:=