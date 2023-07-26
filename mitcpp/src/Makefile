##
## This Makefile compile the sources of the MIT C++ version of Jackos
## The Sources are all the sources code of the MIT C++ version of Jackos
##

## Include the configuration file
include ../config.mk

## By default it build the kernel
all: build

## Building the project
build: __build_message submodules

## Building submodules
submodules:
	@for submodule in $(SUBMODULES); do \
		$(MAKE) -C $$submodule build; \
	done

__build_message:
	@echo -e "$(GREEN)Building $(OS_NAME) Sources...$(NC)"

## Cleaning the project
clean:
	@echo -e "$(GREEN)Cleaning $(OS_NAME) Sources...$(NC)"
	@for submodule in $(SUBMODULES); do \
		$(MAKE) -C $$submodule clean; \
	done

## Building sources
fclean: clean
	@echo -e "$(GREEN)Full Cleaning $(OS_NAME) Sources...$(NC)"
	@for submodule in $(SUBMODULES); do \
		$(MAKE) -C $$submodule fclean; \
	done

## Rebuilding sources
re: fclean build
