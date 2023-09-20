##
## Source Makefile
## This Makefile compiles the OS
##
## @author: pulk66-s
## last update: 2023.09.20
##

# Relative path to the root of the project, useful for the config.mk file
RELATIVE_ROOT_PATH	:=	..

# include config Makefile
include ../mk/config.mk

# All the existing dirs to build
BUILD_DIRS	:=

# Including all sub makefiles
include ./boot/Makefrag
include ./kernel/Makefrag

# default root: Build the OS
all: os_build

os_build: 
	@echo -e "${GREEN}Building ${PROJECT_NAME}${NC}"
	@for dir in $(BUILD_DIRS); do \
		mkdir -p $(BIN_FOLDER)/$$dir; \
	done
	@echo -e "${GREEN}Building ${PROJECT_NAME} done${NC}"
