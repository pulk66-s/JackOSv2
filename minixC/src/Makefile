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

# default root: Build the OS
all: os_build

# Including all sub makefiles
include ./boot/Makefrag
include ./kernel/Makefrag

os_build: _bin_arch ${BINARIES}
	@echo -e "${GREEN}Building ${PROJECT_NAME} done${NC}"
	touch ${KERNEL_IMG}
	echo ${BINARIES}
# Add the current binaries to the main Image
	@for bin in $(BINARIES); do \
		echo -e "${YELLOW}Copying $$bin${NC}"; \
		dd if=$(BIN_DIR)/$$bin conv=notrunc >> ${KERNEL_IMG}; \
	done
# Debug
	@echo -e "${YELLOW}Image size: $$(du -h ${KERNEL_IMG} | cut -f1)${NC}"

_bin_arch:
	@echo -e "${GREEN}Building ${PROJECT_NAME}${NC}"
	@for dir in $(BUILD_DIRS); do \
		echo -e "${YELLOW}Creating dir $$dir${NC}"; \
		mkdir -p $(BIN_DIR)/$$dir; \
	done

# Cleaning the project
clean:
