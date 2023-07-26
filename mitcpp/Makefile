##
## This is the Makefile of the MIT C++ version of Jackos
## MIT C++ version of Jackos is a C++ version of Jackos
## but it's made learning the MIT 2012 6.828 course
##

## Include the configuration file
include config.mk

## Set the environment variable PROJECT_PWD to the current pwd
export PROJECT_PWD := $(shell pwd)

## By default it build the kernel
all: build

## Building the project
build: __build_message
	@$(MAKE) -C $(SRC_DIR) build

__build_message:
	@echo -e "$(GREEN)Building $(OS_NAME)...$(NC)"

## Cleaning the project
clean:
	@echo -e "$(GREEN)Cleaning $(OS_NAME)...$(NC)"
	@$(MAKE) -C $(SRC_DIR) clean

## Full cleaning the project, it calls clean first
fclean: clean
	@echo -e "$(GREEN)Full Cleaning $(OS_NAME)...$(NC)"
	@$(MAKE) -C $(SRC_DIR) fclean

## Rebuilding the project, it calls fclean and build
re: fclean build
