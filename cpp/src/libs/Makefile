##
## This Makefile is used to compile all the libraries in the cpp/src/libs
## directory.  It is called by the top-level Makefile.
##

# Include the configuration file
include ../../config.mk

## Error if no target is specified

LIBS	= ./Types/

all:
	@echo "${COLOR_RED}Error: No target specified on libs Makefile${NO_COLOR}"

build:
	@echo "${COLOR_YELLOW}Building libraries...${NO_COLOR}"
	@for lib in $(LIBS); do \
		$(MAKE) -C $$lib build; \
	done

clean:
	@echo "${COLOR_YELLOW}Cleaning libraries...${NO_COLOR}"
	@for lib in $(LIBS); do \
		$(MAKE) -C $$lib clean; \
	done

fclean:
	@echo "${COLOR_YELLOW}Full cleaning libraries...${NO_COLOR}"
	@for lib in $(LIBS); do \
		$(MAKE) -C $$lib fclean; \
	done
