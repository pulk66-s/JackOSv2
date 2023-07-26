##
## Global Makefile for the Cpp project
## It manages the whole cpp project
##

## Include configuration file
include ./config.mk

ASM_SRC	:=	./boot/

## By default we are building the application
all: build

# Build the application
build: __build_message __build_file_arch
	$(MAKE) -C ./src/

__build_file_arch:
	mkdir -p ./bin

__build_message:
	@echo "$(GREEN)Building the whole application from GLOBAL Makefile...$(NC)"

# Clean the application
clean:
	$(MAKE) -C ./src/ clean

# Full clean the application
fclean:
	$(MAKE) -C ./src/ fclean
	$(RM) -rf ./bin

# Run the tests
tests_run: build
	$(MAKE) -C ./tests/

# Run with qemu
run_qemu:
	$(QEMU) $(QEMU_FLAGS) ./bin/$(OS_NAME).iso

# Rebuilding all the application
re: fclean all