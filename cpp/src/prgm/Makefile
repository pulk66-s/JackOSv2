##
## This Makefile is used to compile all the builtin programs
##

## Include the configuration file
include ../../config.mk

## TTY program directory
TTY_DIR		:= ./tty/

## Error if no target is selected
all:
	@echo "${COLOR_RED}No target selected${NO_COLOR}"
	exit 1

## Build the whole project
build:
	@echo "${COLOR_YELLOW}Building ${PROJECT_NAME} programs...${NO_COLOR}"
	@$(MAKE) -C $(TTY_DIR) build

## Clean the whole project
clean:
	@echo "${COLOR_YELLOW}Cleaning ${PROJECT_NAME} programs...${NO_COLOR}"
	@$(MAKE) -C $(TTY_DIR) clean

