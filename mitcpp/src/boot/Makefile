##
## This Makefile compiles the boot process of the MIT C++ version of Jackos
## It includes all the boot sector and the kernel loading
##

## include the configuration file
include ../../config.mk

## By default it build the kernel
all: build

## Build the kernel
build: __build_message

__build_message:
	@echo -e "$(GREEN)Building $(OS_NAME) Boot...$(NC)"

## Cleaning the project
clean:
	@echo -e "$(GREEN)Cleaning $(OS_NAME) Boot...$(NC)"

## Full cleaning the project, it calls clean first
fclean: clean
	@echo -e "$(GREEN)Full Cleaning $(OS_NAME) Boot...$(NC)"

## Rebuilding the project, it calls fclean and build
re: fclean build