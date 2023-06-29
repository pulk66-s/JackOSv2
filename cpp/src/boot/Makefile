##
## Boot sector compilation Makefile
## It's the OS entry
##

## Include the configuration file
include ../../config.mk

## Project sources

## Boot sector Sources
ASM_SOURCES := boot_sector.s

## Boot sector Objects
ASM_OBJECTS := $(ASM_SOURCES:.s=.o)

## Error if no target is selected
all:
	@echo "${COLOR_RED}No target selected${NO_COLOR}"
	exit 1

__build_message:
	@echo "${COLOR_YELLOW}Building ${PROJECT_NAME} boot...${NO_COLOR}"

## Build the whole boot sector
build: __build_message build_asm

## Build all .s files into .o files
build_asm: $(ASM_OBJECTS)

## Clean all .o files
clean:
	@echo "${COLOR_YELLOW}Cleaning ${PROJECT_NAME} boot...${NO_COLOR}"
	@$(RM) $(ASM_OBJECTS)

## Build each .o file from its .s file
%.o: %.s
	@echo "${COLOR_GREEN}Building $<...${NO_COLOR}"
	$(ASM_CC) $(ASM_FLAGS) $< -o $@
