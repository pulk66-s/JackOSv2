##
## Global Makefile for the Cpp project
## It manages the whole cpp project
##

## Include configuration file
include ./../config.mk

## Project submodules
SUBMODULES	:=	./boot

## By default we are building the application
all: build

# Build the application
build: __build_message build_submodules

# Compile all submodules
build_submodules:
	@echo -e "$(GREEN)Building submodules...$(NC)"
	@for dir in $(SUBMODULES); do \
		$(MAKE) -C $$dir build; \
	done

__build_message:
	@echo -e "$(GREEN)Building the whole application...$(NC)"

# Clean the application
clean: __clean_message clean_submodules

__clean_message:
	@echo -e "$(GREEN)Cleaning the whole application...$(NC)"

# Clean all submodules
clean_submodules:
	@echo -e "$(GREEN)Cleaning submodules...$(NC)"
	@for dir in $(SUBMODULES); do \
		$(MAKE) -C $$dir clean; \
	done

# Clean the application
fclean: __fclean_message fclean_submodules

__fclean_message:
	@echo -e "$(GREEN)Full Cleaning the whole application...$(NC)"

# Clean all submodules
fclean_submodules:
	@echo -e "$(GREEN)Full Cleaning submodules...$(NC)"
	@for dir in $(SUBMODULES); do \
		$(MAKE) -C $$dir fclean; \
	done

# Rebuilding all the application
re: fclean build
