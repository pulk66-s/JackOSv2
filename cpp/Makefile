##
## Main Makefile that compiles everything for the C++ version of the project.
## This Makefile is used to compile everything depending on the target.
## This is used to compile and launch all the project
##

# Include the configuration file
include config.mk

###############################
### NON UPDATABLE VARIABLES ###
###############################

## Source code directory
SRC_DIR 	= src

## Default target
all: build

## Build of all the source code
build:
	@echo "$(COLOR_YELLOW)Building all the project.$(NO_COLOR)"
	$(MAKE) -C $(SRC_DIR) build

## Clean the whole project except the executable
clean:
	$(MAKE) -C $(SRC_DIR) clean

fclean: clean
	$(MAKE) -C $(SRC_DIR) fclean

re: fclean all

run_qemu:
	${QEMU} ${QEMU_FLAGS}
