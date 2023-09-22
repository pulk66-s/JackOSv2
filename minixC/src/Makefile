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

# All the binaries to build
BINARIES	:=

# Including all sub makefiles
include ./boot/Makefrag
include ./kernel/Makefrag

# default root: Build the OS
all: os_build

os_build: _bin_arch ${BINARIES}
	@echo -e "${GREEN}Building ${PROJECT_NAME} done${NC}"
	@dd if=/dev/zero of=$(KERNEL_IMG) count=10000 2> /dev/null
	echo ${BINARIES}
	@for bin in $(BINARIES); do \
		echo -e "${YELLOW}Copying $$bin${NC}"; \
		dd if=${BIN_DIR}/$$bin of=$(KERNEL_IMG) conv=notrunc 2> /dev/null; \
	done

_bin_arch:
	@echo -e "${GREEN}Building ${PROJECT_NAME}${NC}"
	@for dir in $(BUILD_DIRS); do \
		echo -e "${YELLOW}Building $$dir${NC}"; \
		mkdir -p $(BIN_DIR)/$$dir; \
	done

# Cleaning the project
clean:
